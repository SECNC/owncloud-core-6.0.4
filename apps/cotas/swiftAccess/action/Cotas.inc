<?php
set_include_path(
	get_include_path() . PATH_SEPARATOR .
	\OC_App::getAppPath('files_external') . '/3rdparty/phpseclib/phpseclib'
);

	function decryptPassword($encryptedPassword) {
		
		$cipher = getCipher();
		$binaryPassword = base64_decode($encryptedPassword);
		$iv = substr($binaryPassword, 0, 16);
		$cipher->setIV($iv);
		$binaryPassword = substr($binaryPassword, 16);
		return  $cipher->decrypt($binaryPassword);
	}


 function getCipher() {
		if (!class_exists('Crypt_AES', false)) {
			include('Crypt/AES.php');
		}
		$cipher = new Crypt_AES(CRYPT_AES_MODE_CBC);
		$cipher->setKey(\OCP\Config::getSystemValue('passwordsalt'));
		return $cipher;
	}

function getTenantInfos($user,$passwd,$nometenant,$endereco,$bucket){
	//echo $user.' - '. $passwd .' - '. $nometenant .' - '. $endereco . $bucket;
	$passwd =  decryptPassword($passwd);
	$cc = new ConnectionContext();
	$connection = new KeystoneConnection();
	$cc->setConnectionContext($connection);
	$cc->initialize($user, $nometenant, $passwd, trim($endereco));
	
	// Para url mal formadas, revome-se o aviso de erro na hora de abrir uma conexao
	@$cc->realizeAutentication();
	if ($cc->getResponseNumber() == 401 ) {
		echo '$errorManager->setErroMessage("Credencias Inválidas. ".$cc->getResponseNumber(), null);';
		return null;
	} elseif ($cc->getResponseNumber() == 400 || $cc->getResponseNumber() == 404){
		echo '$errorManager->setErroMessage("Não foi possivel realizar o login. Codigo do erro: ". $cc->getResponseNumber(). ", tente logar com outro módulo de autenticacao", null);';
		return null;	
	} elseif ($cc->getResponseNumber() >= 300 && $cc->getResponseNumber() <= 500) {
		echo '$errorManager->setErroMessage("Não foi possivel realizar o login. Codigo do erro: ". $cc->getResponseNumber(), null);';
		return null;	
	} elseif ($cc->getResponseNumber() >= 200 && $cc->getResponseNumber() < 300) {
			
	//	echo "Token: " . $cc->getToken() . '</br>';
	//	echo "Storage URL: " . $cc->getStorageURL() . '</br>';	
	//	echo "Debug:" . $cc->getDebug();		
		$tenant = new Tenant();
		
		
		$tenant->nome = $nometenant;
		$httpConnection = new HttpConnection();
		$httpConnection->addHttpMethodRequest("GET");
		$httpConnection->addNewHeader("X-Auth-Token", $cc->getToken());
		$response = $httpConnection->getResponse($cc->getStorageURL() . '/' . $bucket);//'$swiftURL);
		
		$headers = $httpConnection->getResponseHeaders('X-Container-Meta-Quota-Bytes');
		
		$bytesUsed = 0;
		$bytesQuota = 0;
		$objectsCount = 0;
		$objectsQuota = 0;
		foreach ($headers as $i => $value) {
		//	echo '</br></br>' . $headers[$i];
		//	echo $i;
			//if(strcasecmp($headers[$i], '') != 0){
			
			$split = split(':', $headers[$i]);
			//echo '</br>Header: ' . $header . '</br> Valor: ' . $value;
			
			if(strcasecmp($split[0], 'X-Container-Bytes-Used') == 0) {
				$tenant->bytesUsed = $split[1];
			//	echo 'Detectado Bytes Usados';
			}
			elseif(strcasecmp($split[0], 'X-Container-Meta-Quota-Bytes') == 0) {
				$tenant->bytesQuota = $split[1];
			//	echo 'Detectado Bytes QUOTA';
			}
			elseif(strcasecmp($split[0], 'X-Container-Meta-Quota-Count') == 0) {
				$tenant->objectsQuota = $split[1];
			//	echo 'Detectado Bytes QUOTA';
			}
			elseif(strcasecmp($split[0], 'X-Container-Object-Count') == 0) {
				$tenant->objectsCount = $split[1];
			//	echo 'Detectado Bytes QUOTA';
			}
		}
		return $tenant;
	} else {
		echo '$errorManager->setErroMessage("Não foi possivel realizar o login. Verifique se a URL de autenticacao esta correta.", null);';
		return null;
	}
}
class Tenant{


	public $nome = "";

    public $objectsQuota = 0;
    public $objectsCount = 0;
	
	public $bytesQuota = 0;
	public $bytesUsed = 0;
} 
function readData($isPersonal) {
		$parser = new \OC\ArrayParser();
		if ($isPersonal) {
			$phpFile = OC_User::getHome(OCP\User::getUser()).'/mount.php';
			$jsonFile = OC_User::getHome(OCP\User::getUser()).'/mount.json';
		} else {
			$datadir = \OC_Config::getValue("datadirectory", \OC::$SERVERROOT . "/data");
			$phpFile = OC::$SERVERROOT.'/config/mount.php';
			$jsonFile = $datadir . '/mount.json';
		}
		if (is_file($jsonFile)) {
			$mountPoints = json_decode(file_get_contents($jsonFile), true);
			if (is_array($mountPoints)) {
				return $mountPoints;
			}
		} elseif (is_file($phpFile)) {
			$mountPoints = $parser->parsePHP(file_get_contents($phpFile));
			if (is_array($mountPoints)) {
				return $mountPoints;
			}
		}
		return array();
	}

?>

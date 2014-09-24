<?php 

require __DIR__ . '/../vendor/autoload.php';
use OpenCloud\OpenStack;
use OpenCloud\Common\Constants\Size;

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

function swift ($tenant){

	$data = OC_Gerencia::getTenantsInfo();

	$client = new OpenStack($data[$tenant]["url"], array(
		'username'   => $data[$tenant]["user"],
		'password'   => $data[$tenant]["password"],
		'tenantName' => $tenant
	));

	$objectStoreService = $client->objectStoreService('swift', 'regionOne');

	return $objectStoreService;

}

class OC_Gerencia {

	public function getTenantsInfo(){

		foreach (readData(false) as $users){
			foreach ($users as $user){
				foreach ($user as $backend){
					$tenants[$backend['options']['bucket']] = array ("user"=> $backend['options']['user'],  "tenant" => $backend['options']['tenant']);
				}
			}
		}

		$tenants1 = array_unique($tenants);

		foreach ($tenants1 as $bucket => $tenant){
			foreach (OC_Mount_Config::getAbsoluteMountPoints($bucket) as $mp){
				$result[$tenants1[$bucket]["tenant"]] = array (
							"user"=> $tenants1[$bucket]["user"], 
							"password" => $mp['options']['password'],
							"url" => $mp['options']['url']);
			}
	
		}


		return $result;	
	}

	public function getUsersDetails ($tenant){
		$containers = swift($tenant)->listContainers();

		foreach ($containers as $container) {
			$userquota[$container->getName()] = array (
					"quota" => swift($tenant)->getContainer($container->getName())->getBytesQuota(), 
					"used" => swift($tenant)->getContainer($container->getName())->getBytesUsed());
		}

		return $userquota;
	}

	public function getInstUsed ($tenant){
		foreach (OC_Gerencia::getUsersDetails ($tenant) as $bytes){
   			$allquota += $bytes["quota"];
		}
		
		return $allquota;

	}

	public function getInstDetails ($tenant){
		$bytes["quota"] = OC_Gerencia::getInstQuota ($tenant);
		$bytes["used"] = OC_Gerencia::getInstUsed ($tenant);

		return $bytes;
	}
	
	public function setAllUsersQuota ($tenant, $quota){
		$containers = swift($tenant)->listContainers();

		foreach ($containers as $container) {
			defineQuota($tenant, $container->getName(), $quota);
		}

	}

	public function getInstQuota ($tenant){
		$account = swift($tenant)->getAccount();
		$quota = $account->getDetails()->getProperty('quota-byte');

		if (empty($quota)){
			return null;
		} else {		
			return $quota;
		}
	}

	public function getInstBytesUsed ($tenant){
		$account = swift($tenant)->getAccount();
		$bytes = $account->getDetails()->getProperty('bytes-used');
		
		if (empty($bytes)){
			return 0;
		} else {		
			return $bytes;
		}
	}

	public function getInstNumberOfUsers ($tenant){
		$account = swift($tenant)->getAccount();
		$containers = $account->getDetails()->getProperty('container-count');
		
		return $containers;
	}


	public function removeUser ($tenant, $user){
		OC_User::deleteUser($user);
		OC_Mount_Config::removeMountPoint($user,'user', $user);
		$container = swift($tenant)->getContainer($user);
		$objects = $container->objectList();
		foreach ($objects as $obj){
			$object = $container->getObject($obj->getName());
			$object->delete();
		}
		$container->delete();
	}

	public function defineQuota ($tenant, $user, $quota){
		$container = swift($tenant)->getContainer($user);
		$container->setBytesQuota($quota);
	}

	public function getUserQuotaRemain ($tenant, $user){
		
		$remain = swift($tenant)->getContainer($user)->getBytesQuota() - swift($tenant)->getContainer($user)->getBytesUsed();

		return $remain;
	}


	public function getUserTenant($uid){
		foreach (OC_Mount_Config::getAbsoluteMountPoints($uid) as $mp){
			$tenant = $mp['options']['tenant'];
		}
		return $tenant;	
	}

}



?>

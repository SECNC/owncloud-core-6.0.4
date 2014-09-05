<?php 

require __DIR__ . '/../vendor/autoload.php';
use OpenCloud\OpenStack;
use OpenCloud\Common\Constants\Size;

function swift ($inst){
	$dados = OC_Mount_Config::getAbsoluteMountPoints($inst);
	$mountPoint = array_keys($dados);
	$client = new OpenStack($dados[$mountPoint[0]]["options"]["url"], array(
		'username'   => $dados[$mountPoint[0]]["options"]["user"],
		'password'   => $dados[$mountPoint[0]]["options"]["password"],
		'tenantName' => $dados[$mountPoint[0]]["options"]["tenant"]
	));

	$objectStoreService = $client->objectStoreService('swift', 'regionOne');

	return $objectStoreService;

}

class OC_Gerencia {

	public function addUser($inst, $user, $pwd, $quota){
		OC_User::createUser($user, $pwd);

		swift($inst)->createContainer($user);
		swift($inst)->getContainer($user)->setBytesQuota($quota);

		$dados = OC_Mount_Config::getAbsoluteMountPoints($inst);
		$mountPoint = array_keys($dados);	
		$options = array ("user" => $dados[$mountPoint[0]]['options']['user'], "bucket" => "$user", "region" => "regionOne", "key" => "123", "tenant" => $dados[$mountPoint[0]]["options"]["tenant"], "password" => $dados[$mountPoint[0]]["options"]["password"], "service_name" => "swift", "url" => $dados[$mountPoint[0]]["options"]["url"], "timeout" => "20" );
		OC_Mount_Config::addMountPoint($user, '\OC\Files\Storage\Swift', $options, 'user', $user);
	
	}

	public function getUsersDetails ($inst){
		$containers = swift($inst)->listContainers();

		foreach ($containers as $container) {
			$userquota[$container->getName()] = array (
					"quota" => swift($inst)->getContainer($container->getName())->getBytesQuota(), 
					"used" => swift($inst)->getContainer($container->getName())->getBytesUsed());
		}

		return $userquota;
	}

	public function getInstUsed ($inst){
		foreach (OC_Gerencia::getUsersDetails ($inst) as $bytes){
   			$allquota += $bytes["quota"];
		}
		
		return $allquota;

	}

	public function getInstDetails ($inst){
		$bytes["quota"] = OC_Gerencia::getInstQuota ($inst);
		$bytes["used"] = OC_Gerencia::getInstUsed ($inst);

		return $bytes;
	}
	
	public function setAllUsersQuota ($inst, $quota){
		$containers = swift($inst)->listContainers();

		foreach ($containers as $container) {
			defineQuota($inst, $container->getName(), $quota);
		}

	}

	public function getInstQuota ($inst){
		$account = swift($inst)->getAccount();
		$quota = $account->getDetails()->getProperty('quota-byte');

		if (empty($quota)){
			return 0;
		} else {		
			return $quota;
		}
	}

	public function getInstBytesUsed ($inst){
		$account = swift($inst)->getAccount();
		$bytes = $account->getDetails()->getProperty('bytes-used');
		
		if (empty($bytes)){
			return 0;
		} else {		
			return $bytes;
		}
	}

	public function getInstNumberOfUsers ($inst){
		$account = swift($inst)->getAccount();
		$containers = $account->getDetails()->getProperty('container-count');
		
		return $containers;
	}


	public function removeUser ($inst, $user){
		OC_User::deleteUser($user);
		OC_Mount_Config::removeMountPoint($user,'user', $user);
		$container = swift($inst)->getContainer($user);
		$objects = $container->objectList();
		foreach ($objects as $obj){
			$object = $container->getObject($obj->getName());
			$object->delete();
		}
		$container->delete();
	}

	public function defineQuota ($inst, $user, $quota){
		$container = swift($inst)->getContainer($user);
		$container->setBytesQuota($quota);
	}

}



?>

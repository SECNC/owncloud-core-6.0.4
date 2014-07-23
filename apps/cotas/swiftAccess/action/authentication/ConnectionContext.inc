<?php

require_once 'IConnectionStrategy.inc';

class ConnectionContext{

	private $connectionStrategy;

	public $storageToken;
	public $storageURL;
	public $responseNumber;
	public $debug;

	public function setConnectionContext(IConnectionStrategy $connectionType){

		$this->connectionStrategy = $connectionType;

	}

	public function  initialize($account, $user, $password, $authenticationURL){

		$this->connectionStrategy->setConnectionData($account, $user, $password, $authenticationURL);
	}

	public function realizeAutentication(){
		
			$this->responseNumber = $this->connectionStrategy->authenticate();
			
			$this->storageURL = $this->connectionStrategy->getStorageURL();
			$this->storageToken = $this->connectionStrategy->getStorageToken();
			$this->debug = $this->connectionStrategy->getDebug();
		
		}
		
	public function getToken(){
		return $this->storageToken;
	}
		
	public function getStorageURL(){
		return $this->storageURL;
	}
		
	public function getResponseNumber(){
		return $this->responseNumber;
	}
	public function getDebug(){
		return $this->debug;
	}

}
	
?>
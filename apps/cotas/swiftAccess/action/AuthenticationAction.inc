<?php

require_once 'swiftAccess/connection/HttpConnection.inc';

class AutenticationAction {

	// Parameters for authenticate
	private $autenticationURL;
	private $user;
	private $account;
	private $password;
	private $debug;
	
	// Parameters for authenticate response
	private $storageURL;
	private $storageToken;	

	public function autenticate(){
		
			$httpConnection = new HttpConnection();
			
			$httpConnection->addHttpMethodRequest("GET");
			
			$httpConnection->addNewHeader("X-Auth-User", "$this->account:$this->user");
			$httpConnection->addNewHeader("X-Auth-Key", $this->password);
			
			$httpConnection->getResponse($this->autenticationURL);
			
			if ($httpConnection->getResponseNumber() != 200){
				
				return $httpConnection->getResponseNumber();
			
			}else{
				
				$this->storageToken = trim($httpConnection->getHeaderValuebyName("X-Storage-Token"));
				$this->storageURL = trim($httpConnection->getHeaderValuebyName("X-Storage-Url"));
				$this->debug = "atete";
				
				return $httpConnection->getResponseNumber();
			}
			
	}
	
	public function keystoneAuthenticate(){
		
		$httpConnection = new HttpConnection();
			
		$httpConnection->addHttpMethodRequest("POST");
		$httpConnection->addNewHeader("Content-type","application/json");
		
		$jsonFormatedPostContent =  "{
										\"auth\":{
												\"tenantName\":\"$this->account\",
											    \"passwordCredentials\":{
														\"username\": \"$this->user\",
													    \"password\": \"$this->password\"
									}}}";
		
		$response = $httpConnection->getResponse($this->autenticationURL, $jsonFormatedPostContent);
		
		if ($httpConnection->getResponseNumber() != 200){
		
			return $httpConnection->getResponseNumber();
				
		} else{
			$this->debug = "atete";
			$swiftAcessCredentials = $this->processKeystoneJsonFormatedResponse($response);
			
			$this->storageToken = trim($swiftAcessCredentials[0]);
			$this->storageURL = trim($swiftAcessCredentials[1]);
			return $httpConnection->getResponseNumber();
		}
		
	}
	
	private function processKeystoneJsonFormatedResponse($response){
		
		$arrayFormatedResponse = json_decode($response, true);
		
		// Obtendo o Token
		$swiftAcessCredentials[0] = $arrayFormatedResponse["access"]["token"]["id"];
		
		foreach ($arrayFormatedResponse["access"]["serviceCatalog"] as $index => $arrayOfServices) {
		
			foreach ($arrayOfServices as $type) {
		
				if ($type == "object-store") {
						
					$serviceEndPoints = $arrayOfServices["endpoints"];

					//obtem apenas o primeiro endpoint
					$swiftAcessCredentials[1] = $serviceEndPoints["0"]["publicURL"];
		
				}
			}
		}
		
		return $swiftAcessCredentials;
	}
	
	
	//Getter & Setters
	public function getAutenticationURL(){
		return $this->autenticationURL;
	}
	
	public function setAutenticationURL($autenticationURL){
		$this->autenticationURL = $autenticationURL;
	}
	
	public function getUser(){
		return $this->user;
	}
	
	public function setUser($user){
		$this->user = $user;
	}
	
	public function getAccount(){
		return $this->account;
	}
	
	public function setAccount($account){
		$this->account = $account;
	}
	
	public function getPassword(){
		return $this->password;
	}
	
	public function setPassword($password){
		return $this->password = $password;
	}
	
	public function getStorageURL(){
		return $this->storageURL;
	}
	
	public function getStorageToken(){
		return $this->storageToken;
	}
	
	public function getDebug(){
		return $this->debug;
		
	}
}

?>

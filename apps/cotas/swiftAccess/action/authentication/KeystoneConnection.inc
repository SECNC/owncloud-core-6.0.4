<?php
	
	require_once '\..\..\connection\HttpConnection.inc';
	require_once 'IConnectionStrategy.inc';

	class KeystoneConnection implements IConnectionStrategy {

		// Parameters for authenticate
		private $authenticationURL;
		private $user;
		private $account;
		private $password;
		private $debug;
		
		// Parameters for authenticate response
		private $storageURL;
		private $storageToken;
		
		public function setConnectionData($account, $user, $password, $authenticationURL){
			
			$this->account = $account;
			$this->user = $user;
			$this->password = $password;
			$this->authenticationURL = $authenticationURL;
			
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
		
		public function authenticate(){
			
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
			
			$response = $httpConnection->getResponse($this->authenticationURL, $jsonFormatedPostContent);
			
			if ($httpConnection->getResponseNumber() != 200){
			
				return $httpConnection->getResponseNumber();
			
			} else{
				
				$swiftAcessCredentials = $this->processKeystoneJsonFormatedResponse($response);
				
				$this->storageToken = trim($swiftAcessCredentials[0]);
				$this->storageURL = trim($swiftAcessCredentials[1]);
				
				return $httpConnection->getResponseNumber();
			}
			
		}
		
		//Getter & Setters
		public function getAuthenticationURL(){
			return $this->authenticationURL;
		}
		
		public function setAuthenticationURL($authenticationURL){
			$this->authenticationURL = $authenticationURL;
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
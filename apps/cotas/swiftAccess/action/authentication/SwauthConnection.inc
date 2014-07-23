<?php
	
	require_once 'swiftAccess/connection/HttpConnection.inc';
	require_once 'swiftAccess/action/authentication/IConnectionStrategy.inc';
	

	class SwauthConnection implements IConnectionStrategy {

		// Parameters for authenticate
		private $authenticationURL;
		private $user;
		private $account;
		private $password;
		
		// Parameters for authenticate response
		private $storageURL;
		private $storageToken;
		
		public function setConnectionData($account, $user, $password, $authenticationURL){
			
			$this->account = $account;
			$this->user = $user;
			$this->password = $password;
			$this->authenticationURL = $authenticationURL;
			
		}
		
		public function authenticate(){
			
			$httpConnection = new HttpConnection();
				
			$httpConnection->addHttpMethodRequest("GET");
				
			$httpConnection->addNewHeader("X-Auth-User", "$this->account:$this->user");
			$httpConnection->addNewHeader("X-Auth-Key", $this->password);
				
			$httpConnection->getResponse($this->authenticationURL);
				
			if ($httpConnection->getResponseNumber() != 200){
			
				return $httpConnection->getResponseNumber();
					
			}else{
			
				$this->storageToken = trim($httpConnection->getHeaderValuebyName("X-Storage-Token"));
				$this->storageURL = trim($httpConnection->getHeaderValuebyName("X-Storage-Url"));
			
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
	}
	
?>
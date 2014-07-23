<?php

	interface IConnectionStrategy{
		
		public function setConnectionData($account, $user, $password, $authenticationURL);
		
		public function authenticate();
		
		public function getAuthenticationURL();
		
		public function getUser();
		
		public function getAccount();
		
		public function getPassword();
		
		public function getStorageURL();
		
		public function getStorageToken();
		
		public function getDebug();
		
	}

?>
<?php
	
require_once 'swiftAccess/connection/HttpConnection.inc';
require_once 'swiftAccess/ResourceToolkit.inc';

/**
 * @author felipe 
 * @version 1.0 
 * @since 06/01/2013
 *
 */
class AccountAction {
	
	/**
	 * <p> Get Swift Acount's metaData.</p>
	 *
	 * @param String $authToken
	 * 		  <br/>Authentication token received from auth middleware <br/>
	 *
	 * @param String $storageUrl
	 * 		  <br/>The Swift account url returned from autentication<br/>
	 *
	 * @return Array with response headers.
	 */
	function getAccountMetaData($authToken, $storageURL) {
	
		$httpConnection = new HttpConnection();
	
		$httpConnection->addHttpMethodRequest("HEAD");
		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
	
		$swiftURL = ResourceToolkit::format_url($storageURL, null, null, null); //URL de conexão com o swift
		
		$httpConnection->getResponse($swiftURL);
		
		return $httpConnection->getResponseHeaders();
	
	}
	
	/**
	 * <p> Create an account's metaData.</p>
	 *
	 * @param String $authToken
	 * 		  <br/>Authentication token received from auth middleware <br/>
	 *
	 * @param String $storageUrl
	 * 		  <br/>The Swift account url returned from autentication<br/>
	 *
	 * @param String $MetaDataName
	 * 		  <br/> The name of the metaData that will be created <br/>
	 *
	 * @param String $MetaDataValue
	 * 		  <br/> The value of the metaData that will be created <br/>
	 *
	 * @return Array with response headers.
	 */
	function createAccountMetaData($authToken, $storageURL, $MetaDataName, $MetaDataValue) {
			
			
		if (strstr($MetaDataName, "X-Account-Meta-")) {
	
			$httpConnection = new HttpConnection();
	
			$httpConnection->addHttpMethodRequest("POST");
			$httpConnection->addNewHeader("X-Auth-Token", $authToken);
			$httpConnection->addNewHeader($MetaDataName, $MetaDataValue);
	
			$swiftURL = ResourceToolkit::format_url($storageURL, null, null, null); //URL de conexão com o swift
	
			$rawResponse = $httpConnection->getResponse($swiftURL);
	
			return $httpConnection->getResponseHeaders();
	
				
		}else{
	
			throw new Exception("prefix your MetaData name with 'X-Account-Meta-' ");
		}
			
	}
	
/* 	public function getHeadersAsKeyIndexedArray($authToken, $storageURL) {
		
		$accountHeaders = $this->getAccountMetaData($authToken, $storageURL);
		$accountKeyIndexedArray = array();
		
			foreach ($accountHeaders as $index => $header) {
				
				if ($index == 0) {
					
					continue;
				}else{

					$headerSplited = split(":", $header, 2);
					$accountKeyIndexedArray[$headerSplited[0]] = $headerSplited[1];
				}
			}

		return $accountKeyIndexedArray;
	} */
	
}
?>
<?php

require_once '/../resource/SContainer.inc';
require_once '/../connection/HttpConnection.inc';
require_once '/../ResourceToolkit.inc';

/**
 * ContainerAction implements all the action that can be done in a container. 
 * 
 * 
 * @author felipe 
 * @version 1.0 
 * @since 01/01/2013
 *
 */
 class ContainerAction {
	
 	private $listContainerHeaders;
 	
 	/**
 	 * <p> Return an list of containers in an account. If $query params contains the <b>format</b> query then the response will be in a json or xml format and will be with the container's name and others meta data.</p>
 	 *
 	 * @param String $auth_token
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storage_url
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 *
 	 * @param Array $query_params
 	 * 		  <br/>One of the 4 query optional params for filter or format de response
 	 * 		  o listing containers.<br/>
 	 *
 	 * @return Array with SContainer objects.
 	 */
 	public function listContainers($authToken, $storageURL, $queryParams = null) {
 		
 		$httpConnection = new HttpConnection();
 		
 		$httpConnection->addHttpMethodRequest("GET");
 		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 		
 		$swiftURL = ResourceToolkit::format_url($storageURL, null, null, $queryParams); //URL de conexão com o swift

 		$response = $httpConnection->getResponse($swiftURL);
 		$this->listContainerHeaders = $httpConnection->getResponseHeaders();
 		
 		return $response;
 		 	
 	}
 	
 	public function getListContainersResponseHeaders(){
 		return $this->listContainerHeaders;
 	}
 	
 	/**
 	 * <p> Create a container in an account.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 *
 	 * @param Array $containerName
 	 * 		  <br/> The name of the container that will be created <br/>
 	 *
 	 * @return Array with response headers.
 	 */
 	public function createContainer($authToken, $storageURL, $containerName) {
 			
 		$httpConnection = new HttpConnection();
 			
 		$httpConnection->addHttpMethodRequest("PUT");
 		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 			
 		$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, null, null); //URL de conexão com o swift
 	
 		$httpConnection->getResponse($swiftURL);
		
 		return $httpConnection->getResponseHeaders();
 		
 	}
 	
 	/**
 	 * <p> Remove a container in an account.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 *
 	 * @param Array $containerName
 	 * 		  <br/> The name of the container that will be removed <br/>
 	 *
 	 * @return Array with response headers.
 	 */
 	public function removeContainer($authToken, $storageURL, $containerName) {
 	
 		$httpConnection = new HttpConnection();
 	
 		$httpConnection->addHttpMethodRequest("DELETE");
 		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 	
 		$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, null, null); //URL de conexão com o swift
 	
 		$httpConnection->getResponse($swiftURL);
 	
 		return $httpConnection->getResponseHeaders();
 			
 	}
 	
 	/**
 	 * <p> Get container's metaData.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 *
 	 * @param Array $containerName
 	 * 		  <br/> The name of the container that will provive the metaData<br/>
 	 *
 	 * @return Array with response headers.
 	 */
 	public function getContainerMetaData($authToken, $storageURL, $containerName) {
 	
 		$httpConnection = new HttpConnection();
 	
 		$httpConnection->addHttpMethodRequest("HEAD");
 		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 	
 		$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, null, null); //URL de conexão com o swift
 	
 		$httpConnection->getResponse($swiftURL);
 	
 		return $httpConnection->getResponseHeaders();
 	
 	}
 	
 	/**
 	 * <p> Create a container's metaData.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 *
 	 * @param String $MetaDataName
 	 * 		  <br/> The name of the metaData that will be created <br/>
 	 *
 	 * @param String $MetaDataValue
 	 * 		  <br/> The value of the metaData that will be created <br/>
 	 * 
 	 * @return Array with response headers.
 	 */
 	public function createContainerMetaData($authToken, $storageURL, $containerName, $MetaDataName, $MetaDataValue) {
 		
 		
 		if (strstr($MetaDataName, "X-Container-Meta-") != false) {
 			
 			$httpConnection = new HttpConnection();
 	
 			$httpConnection->addHttpMethodRequest("POST");
 			$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 			$httpConnection->addNewHeader($MetaDataName, $MetaDataValue);
 	
 			$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, null, null); //URL de conexão com o swift
 	
 			$httpConnection->getResponse($swiftURL);
 	
 			return $httpConnection->getResponseHeaders();
 	
 		
 		}else{
 			
 			throw new Exception("prefix your MetaData name with 'X-Container-Meta-' ");
 		}
 		
 	}
 }	
 
?>
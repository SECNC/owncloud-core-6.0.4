<?php

require_once 'swiftAccess/resource/SContainer.inc';
require_once 'swiftAccess/connection/HttpConnection.inc';
require_once 'swiftAccess/ResourceToolkit.inc';

/**
 * ObjectAction implements all the action that can be done in a object. 
 * 
 * 
 * @author felipe 
 * @version 1.0 
 * @since 01/01/2013
 *
 */
 class ObjectAction {
	
 	private $listObjectsHeaders;
 	
 	/**
 	 * <p> Return an list of objects in an account. If $query params contains the <b>format</b> query then the response will be in a json or xml format and will be with the container's name and others meta data.</p>
 	 *
 	 * @param String $AuthToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageURL
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 *
 	 * @param String $containerName
 	 * 		  <br/>The name of the containers that will provide the list of objects<br/>
 	 * 
 	 * @param Array $queryParams
 	 * 		  <br/>One of the 4 query optional params for filter or format de response
 	 * 		  o listing containers.<br/>
 	 * 
 	 * @return Array with SObjects objects.
 	 */
 	function listObjects($authToken, $storageURL, $containerName, $queryParams = null) {
 		
 		$httpConnection = new HttpConnection();
 		
 		$httpConnection->addHttpMethodRequest("GET");
 		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 		
 		$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, null, $queryParams); //URL de conexao com o swift
		
 		$response = $httpConnection->getResponse($swiftURL);
 		$this->listObjectsHeaders = $httpConnection->getResponseHeaders();
 		
 		return $response;
 	}
 	
 	public function getListObjectsResponseHeaders(){
 		return $this->listObjectsHeaders;
 	}
 	
 	/**
 	 * <p> Return an file stored in Swift. This method prints the file in screen.
 	 * To obtain the file as an download, sent the following header tto the browser before call tis method:
 	 * 
 	 *  - Content-Disposition
 	 *  - Content-type
 	 *  - Content-length
 	 * 
 	 * <br/><br/>
 	 * An example of usage is:
 	 * <br/>
 	 * header("Content-Disposition: attachment; filename=".$_GET["object"]);
	 * header("Content-type:". $_GET["kind"]);
	 * header("Content-length:". $_GET["size"]);
 	 * 
 	 * $swiftObject = new ObjectAction();
 	 * $swiftObject->getObjectContent();
 	 * 
 	 * (...)
 	 * 
 	 * </p>
 	 *
 	 * @param String $AuthToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageURL
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 *
 	 * @param String $containerName
 	 * 		  <br/>The name of the containers that will provide the list of objects<br/>
 	 *
 	 * @param Array $queryParams
 	 * 		  <br/>One of the 4 query optional params for filter or format de response
 	 *  		  o listing containers.<br/>
 	 * 
 	 * @return An Swift Object.
 	 * 
 	 */
 	public function getObjectContent($authToken, $storageURL, $containerName, $swiftObject = null, $filename) {
 		
		 if (!$fp = @fopen($filename, "wb")) {
            throw new Exceptions\IOError(sprintf(
                Lang::translate('Could not open file [%s] for writing'),
                $filename
            ));
        }
		
		
 		$httpConnection = new HttpConnection();
 			
 		$httpConnection->addHttpMethodRequest("GET");
 		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 			
 		$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, $swiftObject, null); //URL de conexao com o swift
 		
 		$responseHeaders = $httpConnection->getResponseAsChunks($swiftURL,$fp);
 		
 		//return $responseHeaders;
 		
		
		 fclose($fp);
        
        return $responseHeaders;
 	}
 	
 	/**
 	 * <p> Create a directory in an swift container. all dir created has the mime type application/directory</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 * @param String $containerName
 	 * 		  <br/> The name of the container that will receive the directory <br/>
 	 *
 	 * @param String $dirName
 	 * 		  <br/> The name of the directory that will be created<br/>
 	 *
 	 * @return Array with response headers.
 	 */
 	public function createDirectory($authToken, $storageURL, $containerName, $dirName) {
 		
 		$httpConnection = new HttpConnection();
 		
 		$httpConnection->addHttpMethodRequest("PUT");
 		$httpConnection->addNewHeader("Content-type", "application/directory");
 		$httpConnection->addNewHeader("Content-length", 0);
 		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 		
 		$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, $dirName, null); //URL de conexao com o swift
 		
 		$httpConnection->getResponse($swiftURL);
 		
 		// return $swiftURL;
 		return $httpConnection->getResponseHeaders();
 		
 	}
 	
 	/**
 	 * <p> Upload a Object in an container.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 * @param String $containerName
 	 * 		  <br/> The name of the container that will receive the object <br/>
 	 *
 	 * @param String $swiftDirName [Optional]
 	 * 		  <br/> The name of the dir that will receive the object (if exist)<br/>
 	 * 
 	 * @param Array $objectInfo
 	 * 		  <br/> An array with the path, name, the size and the type of the file tha will be uploaded <br/>
 	 * 
 	 * @param Array $metaData [Optional]
 	 * 		  <br/> The metadata tha will be sent together with the object<br/>
 	 * 
 	 * @return Http response code.
 	 */
 	function uploadObject($authToken, $storageURL, $containerName, $swiftDirName = null, array $objectInfo, array $metaData = null) {
 		
 		/*
 		 * TODO add meta data to uploaded file
 		 */	
 		
 		//URL de conexao com o swift
 		if (is_null($swiftDirName)) {
 			
 			$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, $objectInfo["name"], null);
 		
 		} else {
 			
 			$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, $swiftDirName."/".$objectInfo["name"], null); 
 		}
 			
 		 	
 		//Arquivo que será enviado
 		$tempFileHadler = fopen($objectInfo["path"], "rb");
 		
 		$ch = curl_init($swiftURL);
 		
 		curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 2);
 		
 		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
 		
 		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false); #Permite a utilização de certificado auto assinado
 		
 		curl_setopt($ch, CURLOPT_HTTPHEADER, array("Content-type: ".$objectInfo["type"], "X-Auth-Token: $authToken")); # Um array com os headers http adicionados a requisição
 		
 		curl_setopt($ch, CURLOPT_PUT, true); #True/1 para realizar uma requisição HTTP PUT. Precisa queas opções CURLOPT_FILE, CURLOPT_FILESIZE estejam setadas também para executar.
 		
 		curl_setopt($ch, CURLOPT_INFILE, $tempFileHadler); # Arquivo que será lido para o upload
 		
 		curl_setopt($ch, CURLOPT_INFILESIZE, $objectInfo["size"]);  # Tamanho do arquivo que será enviado
 		
 		curl_exec($ch);
 		
 		$http_status = curl_getinfo($ch, CURLINFO_HTTP_CODE);
 		
 		curl_close($ch);
 		
 		fclose($tempFileHadler);
 		
		return $http_status;
		 		
 	}
 	
 	/**
 	 * <p> Remove a Swift Object in an account.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 * @param String $containerName
 	 *		  <br/>The name of the container that will provide the object to delete<br/>
 	 *
 	 * @param String $objectName
 	 * 		  <br/> The name of the object that will be removed <br/>
 	 *
 	 * @return Array with response headers.
 	 */
 	function removeObject($authToken, $storageURL, $containerName, $swiftObject) {
 	
 		$httpConnection = new HttpConnection();
 	
 		$httpConnection->addHttpMethodRequest("DELETE");
 		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 		
 		$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, $swiftObject, null); //URL de conexï¿½o com o swift
 		
 		$rawResponse = $httpConnection->getResponse($swiftURL);
 	
 		return $httpConnection->getResponseHeaders();
 			
 	}
 	
 	/**
 	 * <p> Get Swift Object's metaData.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 * @param String $containerName
 	 *		  <br/>The name of the container that will provide the object<br/>
 	 *
 	 * @param SObject $objectName
 	 * 		  <br/> The name of the object that will provide the metaData<br/>
 	 *
 	 * @return Array with response headers.
 	 */
 	function getObjectMetaData($authToken, $storageURL, $containerName, $objectName) {
 	
 		$httpConnection = new HttpConnection();
 	
 		$httpConnection->addHttpMethodRequest("HEAD");
 		$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 	
 		$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, $objectName, null); //URL de conexï¿½o com o swift
 	
 		$rawResponse = $httpConnection->getResponse($swiftURL);
 	
 		return $httpConnection->getResponseHeaders();
 	
 	}
 	
 	/**
 	 * <p> Create an Object's metaData.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 * 
 	 * @param String $containerName
 	 *		  <br/>The name of the container that will provide the object<br/>
 	 *
 	 * @param SObject $objectName
 	 * 		  <br/> The name of the object that will receive the metaData<br/>
 	 * 
 	 * @param String $MetaDataName
 	 * 		  <br/> The name of the metaData that will be created <br/>
 	 *
 	 * @param String $MetaDataValue
 	 * 		  <br/> The value of the metaData that will be created <br/>
 	 * 
 	 * @return Array with response headers.
 	 */
 	function createObjectMetaData($authToken, $storageURL, $containerName, $objectName, $MetaDataName, $MetaDataValue) {
 		
 		
 		if (strstr($MetaDataName, "X-Object-Meta-") != false or $MetaDataName == "X-Delete-At"
 				or $MetaDataName= "X-Delete-After") {
 			
 			$httpConnection = new HttpConnection();
 	
 			$httpConnection->addHttpMethodRequest("POST");
 			$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 			$httpConnection->addNewHeader($MetaDataName, $MetaDataValue);
 	
 			$swiftURL = ResourceToolkit::format_url($storageURL, $containerName, $objectName, null); //URL de conexï¿½o com o swift
 	
 			$rawResponse = $httpConnection->getResponse($swiftURL);
 	
 			return $httpConnection->getResponseHeaders();
 	
 		
 		}else{
 			
 			throw new Exception("prefix your MetaData name with 'X-Object-Meta-' ");
 		}
 		
 	}
 	
 	/**
 	 * <p> Copy an Object to a container/folder to another in the same account.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 * @param String $sourceContainerName
 	 *		  <br/>The name of the container that will provide the object to be copied<br/>
 	 *
 	 * @param SObject $sourceObjectName
 	 * 		  <br/>The name of the object that will be copied<br/>
 	 *
 	 * @param String $DestinationContainerName
 	 * 		  <br/>The name of the container that will recive the copied object<br/>
 	 *
 	 * @param String $DestinationObjectName
 	 * 		  <br/>The name of the copied object<br/>
 	 *
 	 * @return Array with response headers.
 	 */
 	function copyObject($authToken, $storageURL, $sourceContainerName, $sourceObjectName, $DestinationContainerName, $DestinationObjectName) {
 	
 			$httpConnection = new HttpConnection();
 	
 			$httpConnection->addHttpMethodRequest("COPY");
 			$httpConnection->addNewHeader("X-Auth-Token", $authToken);
 			$httpConnection->addNewHeader("Destination", "/$DestinationContainerName/$DestinationObjectName");
 	
 			$swiftURL = ResourceToolkit::format_url($storageURL, $sourceContainerName, $sourceObjectName, null); //URL de conexï¿½o com o swift
 	
 			$rawResponse = $httpConnection->getResponse($swiftURL);
 	
 			return $httpConnection->getResponseHeaders();
 	
 	}
 	
 	/**
 	 * <p> Generate a temporary URL of a object for public access.</p>
 	 *
 	 * @param String $authToken
 	 * 		  <br/>Authentication token received from auth middleware <br/>
 	 *
 	 * @param String $storageUrl
 	 * 		  <br/>The Swift account url returned from autentication<br/>
 	 *
 	 * @param String $sourceContainerName
 	 *		  <br/>The name of the container that will provide the object to be copied<br/>
 	 *
 	 * @param SObject $sourceObjectName
 	 * 		  <br/>The name of the object that will be copied<br/>
 	 *
 	 * @param String $DestinationContainerName
 	 * 		  <br/>The name of the container that will recive the copied object<br/>
 	 *
 	 * @param String $DestinationObjectName
 	 * 		  <br/>The name of the copied object<br/>
 	 *
 	 * @return Array with response headers.
 	 */
 	function shareObject($storageURL, $objectPathName, $accountKey, $expiresTime) {
 		
 		$base= $storageURL;
 		$method = 'GET';
 		$expires = $expiresTime;
 		$key= $accountKey;
 		$path= $objectPathName;
 		$hmac_data="$method\n$expires\n$path";
 		$signature=hash_hmac('sha1',$hmac_data,$key);
 		$temp_url="$base$path?temp_url_sig=$signature&temp_url_expires=$expires\n";
 		
 		return $temp_url;
 	}
 	
 	/*
 	 * 
 	 * <?php
$method = 'GET';
$base = $argv[1];
$path = $argv[2];
$key = $argv[3];
$expires = time() + $argv[4];
$hmac_body = "$method\n$expires\n$path";
$sig = hash_hmac('sha1', $hmac_body, $key);
echo "$base$path?temp_url_sig=$sig&temp_url_expires=$expires\n";
?>
 	 * 
 	 */
 }	
 
?>
<?php

require_once 'resource/SObject.inc';
require_once 'resource/SContainer.inc';

class ResourceToolkit {

	/**
	 * <p> Return TRUE if all the query are valid, and FALSE otherwise</p>
	 *
	 *
	 * @param Array $queryParams
	 * 		  <br/>One of the 4 query optional params for filter or format de response
	 * 		  o listing containers.<br/>
	 *
	 */
	private function valid_params($queryParams) {

		//obtém os tipo de query
		$query_type = array_keys($queryParams);


		//verifica se tem algum tipo de query inválido, isto é, que não seja limit, marker, end_marker ou format
		foreach ($query_type as $query_value) {

			if  ($query_value == "limit" or $query_value == "marker" or
					$query_value == "end_marker" or $query_value == "format" or
					$query_value == "delimiter" or $query_value == "prefix" or $query_value == "path"){

				// Nao faz nada.

			}else {

				return false;
			}

		}

		// somente retorna true se dentro das array $query_types houverem apenas query validas
		return true;

	}

	/**
	 * <p> Return a formatted url with given querys and encoded with RFC 1738 format.</p>
	 *
	 * @param String $storageURL
	 * 		  <br/>The Swift account url returned from autentication<br/>
	 *
	 * @param String $containerName
	 * 		  <br/>the name  of the container<br/>
	 *
	 * @param String $objectName
	 * 		  <br/>the name  of the object<br/>
	 *
	 * @param Array $queryParams
	 * 		  <br/>One of the 4 query optional params to filter or format de response
	 * 		  o listing containers.<br/>
	 *
	 */
	public static function format_url($storageURL, $containerName=null, $objectName=null, $queryParams = null) {

		if ($queryParams != null){
				
			if (self::valid_params($queryParams)) {

				$formatedParams = "?".http_build_query($queryParams);

				if ( $containerName != null)
					$containerName = "/".rawurlencode($containerName);

				if ( $objectName != null )
					$objectName = "/".rawurlencode($objectName);

				$storageURL .= $containerName.$objectName.$formatedParams;

			} else{

				throw new Exception("Um dos parâmetros para 'query' não é válido");

			}
				
		}else {
				
			if ( $containerName != null)
				$containerName = "/".rawurlencode($containerName);
				
			if ( $objectName != null )
				$objectName = "/".rawurlencode($objectName);
				
			$storageURL .= $containerName.$objectName;
				
		}

		return $storageURL;
	}

	private static function jsonResponseToResourceList($rawResponse, $resourceType){

		$arrayFormatedResponse = json_decode($rawResponse, true);
			
		$resourceList = array();
		$index = 0;

		if (strtolower($resourceType) == "container") {

			foreach ($arrayFormatedResponse as $container) {
					
				$resourceList[$index] = new SContainer($container["name"], $container["count"], $container["bytes"]);
				$index++;
			}
			
		} elseif (strtolower($resourceType) == "object"){
				
			foreach ($arrayFormatedResponse as $object) {
			
				$resourceList[$index] = new SObject($object["name"], $object["bytes"], $object["hash"], $object["content_type"], $object["last_modified"]);
				$index++;
			}
			
		}else{

			throw new Exception("The resource type must be 'container' or 'object', but caught: $resourceType <br/>");
		}
		
		return $resourceList;
		
	}
	
	public static function getFormatedResponse($responseBody, $queryParams, $resourceKind){
		
		//verifica se há a query format
		if (array_key_exists("format", $queryParams)) {
				
			//Se houver, e a resposta for em json, a leitura sera realizada do retorno em json
			if (strtolower($queryParams["format"]) == "json") {
		
				$jsonFormatedAsObjectResponse = ResourceToolkit::jsonResponseToResourceList($responseBody, $resourceKind);
		
				return $jsonFormatedAsObjectResponse;
		
			}elseif(strtolower($queryParams["format"]) == "xml"){
		
				//codigo para processar resposta em xml
				throw new Exception("XML response, yet is not supported");
		
			}else {
		
				throw new Exception($queryParams["format"].", this kind of formated response is not supported");
			}
		
		}
		
	}
	
	public static function getBestSizeRepresentation($swiftResource){
	
		if ($swiftResource->getTotBytes() < 1024) {
				
			return round($swiftResource->getTotBytes(),2)." Bytes";
	
		} elseif($swiftResource->getTotInKB() < 1024){
				
			return round($swiftResource->getTotInKB(), 2)." KB";
	
		} elseif($swiftResource->getTotInMB() < 1024){
				
			return round($swiftResource->getTotInMB(), 2)." MB";
				
		} else{
				
			return round($swiftResource->getTotInGB(), 2)." GB";
		}
	
	}
	
	public static function getBestSizeRepresentationIntValue($size){
	
		if ($size < 1024) {
	
			return round($size,2)." Bytes";
	
		} elseif($size < (1024*1024)){
	
			return round(($size/1024), 2)." KB";
	
		} elseif($size < (1024*1024*1024)){
	
			return round(($size/(1024*1024)), 2)." MB";
	
		} else{
	
			return round(($size/(1024*1024*1024)), 2)." GB";
		}
	
	}
	
	public static function getHeadersAsKeyIndexedArray($reponseHeader) {
	
		$headers = $reponseHeader;
		$headersKeyIndexedArray = array();
	
		foreach ($headers as $index => $header) {
	
			if ($index == 0) {
					
				continue;
			}else{
	
				$headerSplited = split(":", $header, 2);
				$headersKeyIndexedArray[$headerSplited[0]] = $headerSplited[1];
			}
		}
	
		return $headersKeyIndexedArray;
	}
	
}

?>
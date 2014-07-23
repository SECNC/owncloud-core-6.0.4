<?php

/**
 * 
 * SObject is a class that represent a object in Openstack-Swift context.
 * 
 * This class join five attributes of a object, they are:
 * 	
 * 	- The name;
 *  - The hash value o f the object;
 *  - the content type (Mime-type) of the object;
 *  - The date of the last modification of the object;
 *  - The total bytes consumed by the object in bytes, Kbyte, Mbytes e Gbytes; 
 * 
 * @author felipe
 * @version 1.0
 * @since 30/12/2012
 *
 */
class SObject {

	private $name;
	private $totBytes;
	private $totInKB;
	private $totInMB;
	private $totInGB;
	private $hash;
	private $contentType;
	private $lastModified;
	 
	function __construct($name, $totBytes, $hash, $contentType, $lastModified) {
		
		$this->name = $name;
		$this->totBytes = $totBytes;
		$this->hash = $hash;
		$this->contentType = $contentType;
		$this->lastModified = $lastModified;
		  
	}

	//Getters
	public function getName(){
		return $this->name;
	}
  	
	
  	public function getTotBytes(){
  		return $this->totBytes;
  	}
  	
  	public function getTotInKB(){
  		$this->totInKB = $this->totBytes/1024;
  		return $this->totInKB;	
  	}

	public function getTotInMB(){
  		$this->totInMB = $this->totInKB/1024;
  		return $this->totInMB;	
  	}
  	
  	public function getTotInGB(){
  		$this->totInGB = $this->totInMB/1024;
  		return $this->totInGB;
  	}
  	
  	public function getHash(){
  		return $this->hash;
  	}
  	
  	public function getContentType(){
  		return $this->contentType;
  	}
  	
  	public function getLastModified () {
  		return $this->lastModified;
  	}
}  
 
?>
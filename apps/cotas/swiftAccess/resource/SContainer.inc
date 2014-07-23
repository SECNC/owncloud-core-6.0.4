<?php

/**
 * 
 * SContainer is a class that represent a container in Openstack-Swift context.
 * 
 * This class join three attributes of a container, they are:
 * 	
 * 	- The name;
 *  - The total number of objects in the container;
 *  - The total bytes consumed by the container in bytes, Kbyte, Mbytes e Gbytes; 
 * 
 * @author felipe
 * @version 1.0
 * @since 30/12/2012
 *
 */
class SContainer {

	private $name;
	private $totObjects;
	private $totBytes;
	private $totInKB;
	private $totInMB;
	private $totInGB;
	
	function __construct($name, $totObjects, $totBytes) {
		
		$this->name = $name;
		$this->totObjects = $totObjects;
		$this->totBytes = $totBytes;
	
	}

	//Getters
	public function getName(){
		return $this->name;
	}

	public function getTotObjects(){
		return $this->totObjects;
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
  	
}  
 
?>
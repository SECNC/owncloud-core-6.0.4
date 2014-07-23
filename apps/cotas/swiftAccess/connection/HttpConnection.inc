<?php

/**
 * @author felipe 
 * @version 1.0 
 * @since 01/01/2013
 *
 */
class HttpConnection {
	
	private $headersToSend;
	private $responseHeaders;
	private $httpMethodRequest;
	private $httpResponseNumber;
	
	public function getResponse($swiftURL, $postContent = null){
	
			if (empty($postContent)) {

				$options = array(
						'http' => array (
								'method' => strtoupper($this->httpMethodRequest),
								'header' => $this->headersToSend,
						));
			
			}else{
				$options = array(
						'http' => array (
								'method' => strtoupper($this->httpMethodRequest),
								'header' => $this->headersToSend,
								'content' => $postContent,
						));
			}
			
			$context = stream_context_create($options);
			
			$response = file_get_contents($swiftURL,false, $context);
			
			$this->responseHeaders =$http_response_header;
			$this->httpResponseNumber = $this->extractHttpResponseNumber($this->responseHeaders);
			
			return $response;


	}
	
	public function getResponseAsChunks($swiftURL){

		$options = array(
				'http' => array (
						'method' => strtoupper($this->httpMethodRequest),
						'header' => $this->headersToSend,
				));

		$context = stream_context_create($options);
			
		$fp = fopen($swiftURL, 'rb', false, $context);
			
		//Obtem o corpo da mensagem HTTP em parte e exibe na tela
		while($chunk = fread($fp, 1024*1024)) {
			print $chunk;
			flush();
		}
		
		fclose($fp);
		
		$this->responseHeaders =$http_response_header;
		$this->httpResponseNumber = $this->extractHttpResponseNumber($this->responseHeaders);
		
		return $this->responseHeaders;
	}
	
	public function addNewHeader($headerName, $headerValue){
		$this->headersToSend[] = "$headerName:$headerValue";
	}
	
	public function addHttpMethodRequest($httpMethodRequest){
		$this->httpMethodRequest = $httpMethodRequest;
	}
	
	public function getHeaderValuebyName($headerName) {
		
		if (!empty($this->responseHeaders)) {

			foreach ($this->responseHeaders as $header) {
					
				$headerSplited = split(":", $header, 2);
					
				if ($headerSplited[0] == $headerName) {
			
					//retorna o valor do header
					return $headerSplited[1];
				}
			}
			
		
		}else {

			throw new Exception("No response headers.");
			
		}
			
	}
	
	private function extractHttpResponseNumber($responseHeaders){
		$responseNumber = split(" ", $responseHeaders[0]);
		return $responseNumber[1];	
	}
	
	public function getResponseInChuncks($swiftURL, array $headers){
			//falta implementar			
	}
	
	public function getHeadersToSend() {
		return $this->headersToSend;
	}
	
	public function getHttpResponseNumber(){
		return $this->httpResponseNumber;
	} 
	
	public function getResponseHeaders() {
		return $this->responseHeaders;
	}
	
	public function getHttpMethodRequest() {
		return $this->httpMethodRequest;
	}
	
	public function getResponseNumber() {
		return $this->httpResponseNumber;
	}
}
?>
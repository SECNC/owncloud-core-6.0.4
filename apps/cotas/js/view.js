
	function altera(porcentagem,name){
		var name_element = document.getElementById( name ) ;
		
		name_element.style.width = porcentagem + "%";
		
		if(porcentagem < 25){
			name_element.style.backgroundColor = "#86e01e" ;
		}
		else if (porcentagem < 50){
			name_element.style.backgroundColor = "#f2b01e" ;
		}
		else if (porcentagem < 75){
			name_element.style.backgroundColor = "#f27011" ;
		}
		else if (porcentagem < 101){
			name_element.style.backgroundColor = "#f63a0f" ;
		}
	}
	
	function teste(){
		var name_element = document.getElementById( 'progress-bar' ) ;
		name_element.style.width = "80%";
		name_element.style.backgroundColor = "#F00" ;

	}
	
		
function ajax(){
	var $this = $(this),data = $this.data();
//	alert(window.location);
	$.ajax({
		url:OC.filePath('cotas', 'ajax', 'getinfo.php'),
		type:"POST",
		dataType:"JSON",
		data:{user:data.user,tenant:data.nomeexibicao,acao:"tenant",tipo:data.tipo},
		success:function(data){
			if(data == null){
				return;
			}
			if(data.bytesUsed > 1073741824){
                                $this.find(".bytes-used").html((data.bytesUsed/1024/1024/1024).toFixed(2) + ' Gb');

                        }else if(data.bytesUsed > 1048576){
				$this.find(".bytes-used").html((data.bytesUsed/1024/1024).toFixed(2) + ' Mb');

			}else if(data.bytesUsed > 1024){
                                $this.find(".bytes-used").html((data.bytesUsed/1024).toFixed(2) + ' Kb');

                        }else{
				$this.find(".bytes-used").html(data.bytesUsed + ' Bytes');
			}

                        if(data.bytesQuota > 1073741824){
                                $this.find(".bytes-quota").html('de ' + (data.bytesQuota/1024/1024/1024).toFixed(2) + ' Gb');

                        }else if(data.bytesQuota > 1048576){
                                $this.find(".bytes-quota").html('de ' + (data.bytesQuota/1024/1024).toFixed(2) + ' Mb');

                        }else if(data.bytesQuota > 1024){
                                $this.find(".bytes-quota").html('de ' + (data.bytesQuota/1024).toFixed(2) + ' Kb');

                        }else if(data.bytesQuota <= 0){
                                $this.find(".bytes-quota").html('Ilimitado');
                        }else{
				$this.find(".bytes-quota").html('de ' + data.bytesQuota + ' Bytes');	
			}


			
			$this.find(".objects-count").html(data.objectsCount + ' Objetos');


			if(data.objectsQuota <= 0){
                                $this.find(".objects-quota").html('Ilimitado');
                        }else{
                                $this.find(".objects-quota").html('de ' + data.objectsQuota + ' Objetos');
                        }

			
			//alert(data.bytesUsed/data.bytesQuota *100 +"%");
			//var porcentagem = data.objectsCount/data.objectsQuota *100,
			var porcentagem = data.bytesUsed/data.bytesQuota *100;
			
			if(porcentagem > 100){
				p = $this.find(".progress-bar").width("100%");
		
			}
			else if(porcentagem <0){
						p = $this.find(".progress-bar").width(porcentagem +"0%");
		
			}else{
				p = $this.find(".progress-bar").width(porcentagem +"%");
			}

			if(porcentagem < 25){
				p.css("background-color","#86e01e");
			}
			else if (porcentagem < 50){
					p.css("background-color","#f2b01e");
			}
			else if (porcentagem < 75){
				p.css("background-color","#f27011");
			}
			else if (porcentagem > 100){
				p.css("background-color","#555");
			}else {				
				p.css("background-color","#f63a0f");
		
			}
		
		}
	});
	
}

$(function () {

	console.log($(".personalblock"));
	$(".personalblock").each(ajax);
  
  })
<?php
$info = $_['info'];
$user = $_['user'];
	
function printProgressBar($nomeexibicao,$user,$datatenant,$datatipo){
		echo '<div id="quota" class="personalblock quota-' . $nomeexibicao . '" data-nomeexibicao="' . $nomeexibicao . '" data-user="' . $user . '" data-tenant="'.$datatenant.'" data-tipo="'.$datatipo.'" >';
		echo '<strong>' . $nomeexibicao . '</strong>';
		echo '<section class="container">';
		echo '<div class="progress">';
		echo '<div class="progress-bar" name="progress-bar" id="progress-bar"></div>';
		echo '</div>';
		echo '</section>';
		echo '<div >';
	}
function printDescription(){
		echo 'Você usou <strong> <span class="bytes-used">0</span></strong> do seu espaço de <strong><span class="bytes-quota">0</span></strong></br>';
		echo 'Você usou <strong> <span class="objects-count">0</span></strong> do seu espaço de <strong> <span class="objects-quota">0</span></strong>';
		echo '</br>';
		echo '</div></div></br>';
		
}
	
?>

<div id="geral" style="margin-top:1cm;">
<div id="titulo" style="margin: 10px;font-size: 30px;">Cotas:</div></br>

<?php 
	//Pegando nome dos usuários do mount.json
	$users = array_keys($info[user]);
	foreach ($users as $usuariojson){
		if(strcasecmp($usuariojson,$user) == 0) {
			$tenants = array_keys($info[user][$user]);
			foreach ($tenants as $tenant){
				$buff = split('/',$tenant);
				$nomeexibicao = $buff[3];
				if(strcasecmp($info[user][$user][$tenant]['class'],'\OC\Files\Storage\Swift') == 0) {
					printProgressBar($nomeexibicao,$user,$info['user'][$user][$tenant]['options']['tenant'],0);
					printDescription();
				}
			}
		}elseif(strcasecmp($usuariojson,'all') == 0) {
			$tenants = array_keys($info[user]['all']);
			foreach ($tenants as $tenant){
				$buff = split('/',$tenant);
				$nomeexibicao = $buff[3];
				if(strcasecmp($info[user]['all'][$tenant]['class'],'\OC\Files\Storage\Swift') == 0) {
					printProgressBar($nomeexibicao,$user,$info['user']['all'][$tenant]['options']['tenant'],0);
					printDescription();
				}
			}
		}
	}
	
	//Pegando nome dos usuários do mount.json
	$groups = array_keys($info[group]);
	//Pegando Grupos do usuário
	$retorno = \OCP\DB::prepare('select * from oc_group_user where uid=\'' . $user . '\'', null, null)->execute();
	$valor = $retorno->fetchRow();
	while($valor != NULL){
		foreach ($groups as $groupjson){
			if(strcasecmp($groupjson,$valor['gid']) == 0) {
				$tenants = array_keys($info[group][$valor['gid']]);
				foreach ($tenants as $tenant){
					$buff = split('/',$tenant);
					$nomeexibicao = $buff[3];
					if(strcasecmp($info[group][$valor['gid']][$tenant]['class'],'\OC\Files\Storage\Swift') == 0) {
						printProgressBar($nomeexibicao,$valor['gid'],$info['group'][$valor['gid']][$tenant]['options']['tenant'],1);
						printDescription();

					}
				}			
			}
		}
		$valor = $retorno->fetchRow();
	}
?>
</div>
</div>
</div>

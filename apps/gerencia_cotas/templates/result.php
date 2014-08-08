Nova Busca
<form action = "busca.php" method="POST">
<pre>
<input type="text" name="user" autocomplete="off"></input> <input type="submit" value="Buscar" name="enviar"></input>
</pre>
</form>
<?php /* André Avelino da Silva Neto 06-08-2014 */

$usercota = $_["usercota"];

if ($_['result'] == 1): ?>

<?php 
	$i = 0; 
	foreach ($_['users'] as $uid){
		similar_text(strtolower($_['user']), strtolower($uid), $percent);
		if ($percent > 30){ 
			$similar[$i] = $uid; 
			$i++; 
		} 
	} 
?> 

<?php endif; ?>

<?php if ($_['result'] == 2): ?>
Nova cota definida!
<?php endif; ?>

<?php 
	if (empty($similar)){ 
		$vazio = 1;
	}
?>

<?php if ($vazio != 1): ?>

<?php session_start(); $_SESSION['user']=$similar; session_write_close(); ?>

<br></br>
  <table width="100%">
	<tr> 
		<td>Usuário</td> 
		<td>Cota Atual</td> 
		<td>Nova Cota</td> 
	</tr>

<?php foreach($similar as $id): ?>

	<tr>
		<td><?php print($id); ?></td>  
		<td><?php print($usercota["$id"]/(1024*1024)); echo " MB"; ?></td> 
		<td><form action = "definer.php" method="POST"><input type="text" name="cota" maxlength = "4" style="width:42px;"></input><select name="size"><option value= "MB">MB</option><option value= "GB">GB</option> </select> <input type="submit" value="Definir" name="<?php print($id); ?>"></input></form></td>
	</tr>

<?php endforeach; ?>
</table>

<?php endif; ?>

<?php if (($vazio == 1) && ($_['result'] != 2)): ?>
Nenhum resultado encontrado!
<?php endif; ?>


<br><center><font size= "5"><b>GERENCIAMENTO DE USUÁRIOS - <?php print(strtoupper($_['inst'])); ?></b></font><br>

<progress max="100" value= "
<?php $bytes = $_['bytes']; $progress = ($bytes['used']*100)/$bytes['quota']; print($progress); ?>"></progress>  <?php 
		print(number_format($progress, 1)); 
		echo '% ('; 
		if ($bytes["used"]<(1024*1024*1024)){ 
			print(number_format($bytes["used"]/(1024*1024), 2)); 
			echo " MB"; 
		} else {
			print(number_format($bytes["used"]/(1024*1024*1024), 2)); 
			echo " GB";				
		} 
		echo " de ";
		if ($bytes["quota"]<(1024*1024*1024)){ 
			print(number_format($bytes["quota"]/(1024*1024),2)); 
			echo " MB"; 
		} else {
			print(number_format($bytes["quota"]/(1024*1024*1024),2)); 
			echo " GB";				
		} 
		echo " utilizados).";
			?>
</center><br></br>

<center><?php if ($_["confirm"]=="y"): ?>

Confirma exclusão do(a) usuário(a) <b><?php echo " " . $_["usr"]; ?></b>? <form action= "remover.php" method="POST"> 
<input type="submit" value="sim" name="sim" />
<input type="submit" value="não" name="no" /> 

<?php endif; ?>

<?php print($_["msg"]); ?>
</center>

<table width="100%" height="30%">
	<tr> 
		<td>Usuário</td> 
		<td>COTA</td> 
		<td>Nova Cota</td> 
		<td></td>
		<td></td>
	</tr>
<?php foreach($_["userquota"] as $id => $userbytes): ?>

	<tr>
		<td><?php if (strtolower($id) == strtolower($_['inst'])){ echo "<b>"; print($id);  echo " (admin)</b>"; } else { print($id); } ?></td>  
		<td><?php 
			if ($userbytes["quota"]<(1024*1024*1024)){ 
				print($userbytes["quota"]/(1024*1024)); 
				echo " MB"; 
			} else {
				print($userbytes["quota"]/(1024*1024*1024)); 
				echo " GB";				
			}
		?>
		</td> 
		<td>
			<form action = "definer.php" method="POST"><input type="text" name="cota" autocomplete= off maxlength = "4" style="width:20px;height:12px"></input><select style="width:49px;height:25px;font-size:12px" name="size"><option value= "MB">MB</option><option value= "GB">GB</option> </select> <input type="hidden" name="uid" value="<?php print($id); ?>" /> <input type="submit" value="ok" style="width:30px;height:30px" name="definir"></input></form>
		</td>

		<td>
			<progress max="100" value= "<?php $progress = ($userbytes['used']*100)/$userbytes['quota']; print($progress); ?>"></progress>  <?php 
		print(number_format($progress, 1)); 
		echo '% ('; 
		if ($userbytes["used"]<(1024*1024*1024)){ 
			print(number_format($userbytes["used"]/(1024*1024), 2)); 
			echo " MB"; 
		} else {
			print(number_format($userbytes["used"]/(1024*1024*1024), 2)); 
			echo " GB";				
		} 
		echo " de ";
		if ($userbytes["quota"]<(1024*1024*1024)){ 
			print(number_format($userbytes["quota"]/(1024*1024),2)); 
			echo " MB"; 
		} else {
			print(number_format($userbytes["quota"]/(1024*1024*1024),2)); 
			echo " GB";				
		} 
		echo " utilizados).";
			?>	
		</td>


		<td>
			<form action = "remover.php" method="POST"><input type="hidden" name="uid" value="<?php print($id); ?>" /><input type="submit" value="remover" style="width:60px;height:23px;font-size:12px" name="removeuser"></input></form>
		</td>
	</tr>

<?php endforeach; ?>
</table>


<?php if (OC_User::isAdminUser(OC_User::getUser())): ?>
<center>
<br></br>
<a href = "index.php?ref=ger"><button>voltar</button></a>
</center>
<?php endif; ?>

<br><center><font size= "5"><b>GERENCIAMENTO DE INSTITUIÇÕES</b></font></center>
<table width="100%" height="30%">
	<tr> 
		<td>Instituição</td> 
		<td>COTA</td>
		<td></td>
	</tr>

<?php foreach ($_["instquota"] as $inst => $bytes): ?>
	<tr>
		<td> 
			
			<a href ="<?php print($_['ref']); ?>inst.php?inst=<?php print($inst); ?>"><button> <?php print($inst); ?> </button></a>
		</td>
		<td>
			<?php 
				if ($bytes["quota"]<(1024*1024*1024)){ 
					print(number_format($bytes["quota"]/(1024*1024),2)); 
					echo " MB"; 
				} else if ($bytes["quota"]<(1024*1024*1024*1024)){
					print(number_format($bytes["quota"]/(1024*1024*1024),2));
					echo " GB";				
				}else {
					print(number_format($bytes["quota"]/(1024*1024*1024*1024),2));
					echo " TB";
				}
			?> 
		</td>
		<td> 
			<progress max="100" value= "<?php $progress = ($bytes['used']*100)/$bytes['quota']; print($progress); ?>"></progress> 
			<?php 
				print(number_format($progress, 1)); 
				echo '% ('; 
				if ($bytes["used"]<(1024*1024*1024)){ 
					print(number_format($bytes["used"]/(1024*1024), 2)); 
					echo " MB"; 
				} else if ($bytes["used"]<(1024*1024*1024*1024)){ 
					print(number_format($bytes["used"]/(1024*1024*1024), 2)); 
					echo " GB"; 
				} else {	
					print(number_format($bytes["used"]/(1024*1024*1024*1024), 2)); 
					echo " TB";				
				} echo " de ";
				if ($bytes["quota"]<(1024*1024*1024)){ 
					print(number_format($bytes["quota"]/(1024*1024),2)); 
					echo " MB"; 
				} else if ($bytes["quota"]<(1024*1024*1024*1024)){ 
					print(number_format($bytes["quota"]/(1024*1024*1024),2)); 
					echo " GB"; 
				} else {
					print(number_format($bytes["quota"]/(1024*1024*1024*1024),2)); 
					echo " TB";				
				} echo " utilizados).";
			?> 
		</td>
		
	</tr>
<?php endforeach; ?>
</table>


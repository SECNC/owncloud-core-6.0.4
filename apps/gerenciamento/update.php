<?php

require 'lib/access.php';



$sql = 'INSERT INTO OC_Tenants (tenant, user, password, quota) VALUES ()';
$args = array(1);

$query = \OCP\DB::prepare($sql);
$rslt = $query->execute($args);

*/



?>

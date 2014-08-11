<?php
/* André Avelino da Silva Neto 06-08-2014 */
OC_Util::checkAdminUser();

$tmpl = new OCP\Template( 'gerencia_cotas', 'main', 'user' );
$tmpl->printPage();


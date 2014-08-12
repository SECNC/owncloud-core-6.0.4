<?php
require_once __DIR__ . '/Symfony/Component/ClassLoader/UniversalClassLoader.php';

$classLoader = new Symfony\Component\ClassLoader\UniversalClassLoader();
$classLoader->registerNamespaces(array(
    'OpenCloud'      => __DIR__,
    'Guzzle'   => __DIR__,
    'Symfony'  => __DIR__,
  
));
$classLoader->register();

return $classLoader;

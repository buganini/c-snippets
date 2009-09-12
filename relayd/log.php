<?
ini_set('date.timezone', 'Asia/Taipei');
function ip(){return empty($_SERVER['HTTP_X_FORWARDED_FOR'])?$_SERVER['REMOTE_ADDR']:$_SERVER['HTTP_X_FORWARDED_FOR'];}
$fp=fopen('relay.log','a');
fwrite($fp,'['.ip().'] '.date('Y/m/d H:i:s # ').str_replace("\n","\r\n",$_GET['log']));
fclose($fp);
?>
>


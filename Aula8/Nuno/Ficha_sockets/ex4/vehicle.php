<?php
include("db_functions.php");

if(($db = db_connect()) == FALSE) {
  db_report_error("DB access");
  exit(1);
}


if( db_insert($db, $_POST) == FALSE)
{
  db_report_error("DB access");
  exit(2);
}


db_close($db);


  include("header.html");
	echo "Records inserted\n";
    
  include("footer.html");


?>

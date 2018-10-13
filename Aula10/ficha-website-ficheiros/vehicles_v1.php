<?php
include "db_functions.php";

if(($db = db_connect()) == FALSE) {
  db_report_error("DB access");
  exit(1);
}

if( ($res = db_read($db)) === NULL) {
  db_report_error("DB access");
  exit(2);
}

db_close($db);


// Output section
include("header.html");

var_dump($res);

include("footer.html");

?>

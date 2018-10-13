<?php
include("db_functions.php");

if(($db = db_connect()) == FALSE) {
  db_report_error("DB access");
  exit(1);
}

if( ($res = db_read($db)) === FALSE) {
  db_report_error("DB access");
  exit(2);
}

$rec['plate'] = $_POST['plate'];
$rec['owner'] = $_POST['owner'];
$rec['value'] = $_POST['value'];


if( db_insert($db, $rec) == FALSE)
{
  db_report_error("DB access");
  exit(2);
}

db_close($db);

include("header.html");

echo 'Record inserted';

include("footer.html");
?>

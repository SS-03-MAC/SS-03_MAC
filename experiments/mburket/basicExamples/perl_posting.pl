#!/usr/bin/env perl
use CGI;
my $cgi = CGI->new;
$data = $cgi->param('data');

print <<END;
Content-Type: text/html; charset=iso-8859-1

<!DOCTYPE html>
<title>Echoing user input</title>
<h1>Echoing user input</h1>
<p>You typed: $data</p>
END

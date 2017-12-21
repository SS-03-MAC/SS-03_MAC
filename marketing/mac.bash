#! /bin/bash

#############
# Router    #
#############
function main() {
	html_head;
	nav;
	case $SCRIPT_PATH in
		'/')
		homepage;
		;;
		'/about')
		about;
		;;
		'/power')
		power;
		;;
		'/water')
		water;
		;;
		'/feedback')
		;;
	esac
	end;
}


#######################
# Basic HTML Fuctions #		 
#######################
function html_head() {
	echo "<!DOCTYPE>";
	echo "<html lang=\"en\">";
	echo "<head>";
	echo "	<meta charset=\"utf-8\">";
	echo "	<title>CDC</title>";
	echo "</head>";
	echo "<body>" ;
}

function nav() {
	echo "<nav>"
	echo " <ul>"
	echo "	<li><a href=\"/\">Home</li>"
	echo "	<li><a href=\"/about\">About</li>"
	echo "	<li><a href=\"/power\">Power Stats</a>"
	echo "	<li><a href=\"/water\">Water Stat</a>"
	echo "	<li><a href=\"/feedback\">Feedback</a>"
	echo " </ul>"
	echo "</nav>"
}

function end()
{
	echo "</body>"
	echo "</html>"
}

##############
# Site Pages #
##############
function homepage() {
	cat homepage.txt
}

function about() {
	cat about.txt
}

function power() {
	echo ""
}

function water() {
	echo ""
}

function feedback() {
	echo ""
}


main;

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html>
	<head>
		<meta http-equiv="Content-type" content="text/html; charset=utf-8">
		<title>OCRe - Développement</title>
		<link rel="stylesheet" href="style.css" type="text/css" />
		
	</head>

	<body id="wrapper" onload="">
		
		<div id="h1">
			<span class="blur"><a href="indexfr.html">OCRe</a></span><br />
		</div>
		
		<div id="h2">
			L' <font color="black">OCR</font> ultime, par <font color="black">HUGE Software</font><br />
		</div>
		
		<div id="rightcolumn">
			<span class="none"><a href="#"><img src="download.png" alt="" width="" height="" border="0" /></a></span> <br /><br /><br />
			<span class="footer"><a href="http://www.epita.fr/"><img src="epita.jpg" alt="230" width="210" height="" border="0" /></a></span>		
		</div>
		
		<div id="leftcolumn">
			<div class="news"><h1>Développement</h1><br></div>
			<?php
			mysql_connect("localhost", "huge.ocre", "poutreur");
			mysql_select_db("huge.ocre");
			$retour = mysql_query('SELECT * FROM news ORDER BY id DESC LIMIT 0, 5');
			while ($donnees = mysql_fetch_array($retour))
			{
			?>
			
			<div class="news">
			    <h3>
			        <?php echo $donnees['titre']; ?>
			        <em>le <?php echo date('d/m/Y à H\hi', $donnees['timestamp']); ?></em>
			    </h3>
<br>
			    <p>
			    <?php
			    $contenu = nl2br(stripslashes($donnees['contenu']));
			    echo $contenu;
			    ?>
			    </p><br><br>
			</div>
			<?php
			}
			?>
		</div>
		<div id="footer">
			<a href="development.html">this page in English</a>
		</div>
	</body>

</html>
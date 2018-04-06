-- --------------------------------------------------------
-- Host:                         localhost
-- Versione server:              5.1.42-community - MySQL Community Server (GPL)
-- S.O. server:                  Win32
-- HeidiSQL Versione:            9.3.0.4984
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Dump della struttura del database winsigma
CREATE DATABASE IF NOT EXISTS `winsigma` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `winsigma`;


-- Dump della struttura di tabella winsigma.tipi_certificato
CREATE TABLE IF NOT EXISTS `tipi_certificato` (
  `Codice` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Nome` varchar(64) DEFAULT NULL,
  `Descrizione` varchar(64) DEFAULT NULL,
  `LayoutStampa` varchar(40) DEFAULT NULL,
  `LayoutStampaMinuta` varchar(40) DEFAULT NULL,
  `FinestraDialogo` varchar(64) DEFAULT NULL,
  `ProvaA` varchar(64) DEFAULT NULL,
  `ProvaB` varchar(64) DEFAULT NULL,
  `ProvaC` varchar(64) DEFAULT NULL,
  `Dimensione1` varchar(32) DEFAULT NULL,
  `ValoreDim1` int(10) unsigned DEFAULT NULL,
  `Dimensione2` varchar(32) DEFAULT NULL,
  `ValoreDim2` int(10) unsigned DEFAULT NULL,
  `Dimensione3` varchar(32) DEFAULT NULL,
  `ValoreDim3` int(10) unsigned DEFAULT NULL,
  `ProvXcertificato` int(10) unsigned DEFAULT NULL,
  `Maturazione` int(11) DEFAULT '0',
  `Ordinamento` int(11) DEFAULT '0',
  `Variante` tinyint(4) DEFAULT '0',
  `LayoutStampaVerbali` varchar(40) DEFAULT NULL,
  PRIMARY KEY (`Codice`)
) ENGINE=MyISAM AUTO_INCREMENT=17 DEFAULT CHARSET=latin1;

-- Dump dei dati della tabella winsigma.tipi_certificato: 15 rows
/*!40000 ALTER TABLE `tipi_certificato` DISABLE KEYS */;
INSERT INTO `tipi_certificato` (`Codice`, `Nome`, `Descrizione`, `LayoutStampa`, `LayoutStampaMinuta`, `FinestraDialogo`, `ProvaA`, `ProvaB`, `ProvaC`, `Dimensione1`, `ValoreDim1`, `Dimensione2`, `ValoreDim2`, `Dimensione3`, `ValoreDim3`, `ProvXcertificato`, `Maturazione`, `Ordinamento`, `Variante`, `LayoutStampaVerbali`) VALUES
	(1, 'Prova su cubi di calcestruzzo', NULL, 'CertificatoCubi.prn', 'Cubetti.prn', 'CompressioneCubi', 'Compressione su cubi', NULL, NULL, 'Lunghezza (cm)', 15, 'Larghezza (cm)', 15, 'Altezza (cm)', 15, 6, 28, 1, 0, 'Verbali.prn'),
	(2, 'Prova su carote di calcestruzzo indurito', NULL, 'CertificatoCarote.prn', 'Carote.prn', 'CompressioneCarote', 'Compressione su carote', NULL, NULL, 'Diametro (cm)', NULL, 'Altezza (cm)', NULL, NULL, NULL, 6, 0, 3, 0, 'Verbali.prn'),
	(3, 'Prova su barre di acciao da c.a.', NULL, 'CertificatoBarre.prn', 'AcciaioCA.prn', 'TrazionePiegamentoBarre', 'Trazione barre', 'Piegamento barre', NULL, 'Diametro(mm)', NULL, 'Lunghezza(cm)', NULL, NULL, NULL, 6, 0, 5, 0, 'Verbali.prn'),
	(4, 'Prova di trazione su profilati in acciaio', NULL, 'CertificatoTrazioneProfilati.prn', 'AcciaioLaminati.prn', 'TrazioneProfilati', 'Trazione su profilati', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 6, 0, 6, 0, 'Verbali.prn'),
	(5, 'Prova di resilienza su profilati in acciaio', NULL, 'CertificatoResilienzaProfilati.prn', 'MinutaResilienza.prn', 'ResilienzaProfilati', 'Resilienza su profilati', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 6, 0, 7, 0, 'Verbali.prn'),
	(6, 'Prova su reti elettrosaldate', NULL, 'CertificatoReti.prn', 'MinutaReti.prn', 'TrazioneReti', 'Trazione su reti', 'Distacco sul nodo', NULL, 'Diametro(mm)', NULL, NULL, NULL, NULL, NULL, 6, 0, 8, 0, 'Verbali.prn'),
	(7, 'Prova su trecce o trefoli', NULL, 'CertificatoTrefoli.prn', NULL, 'TrazioneTrefoli', 'Trazione su trefoli', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 10, 0, 9, 0, 'Verbali.prn'),
	(8, 'Prova su cubi di calcestruzzo UNI EN 12390-3/2003', NULL, 'CertificatoCubi2003.prn', 'Cubetti2003.prn', 'CompressioneCubi', 'Compressione su cubi', NULL, NULL, 'Lunghezza (mm)', 150, 'Larghezza (mm)', 150, 'Altezza (mm)', 150, 6, 28, 2, 1, 'Verbali.prn'),
	(9, 'Prova su carote di calcestruzzo indurito UNI EN 12390-3/2003', NULL, 'CertificatoCarote2003.prn', 'Carote.prn', 'CompressioneCarote', 'Compressione su carote', NULL, NULL, 'Diametro (mm)', NULL, 'Altezza (mm)', NULL, NULL, NULL, 6, 0, 4, 0, 'Verbali.prn'),
	(10, 'Prova su barre da c.a. B450', NULL, 'CertificatoBarreB450.prn', 'AcciaioCAB450.prn', 'TrazionePiegamentoBarre', 'Trazione barre', 'Piegamento barre', NULL, 'Diametro(mm)', NULL, 'Lunghezza(cm)', NULL, NULL, NULL, 6, 0, 10, 1, 'Verbali.prn'),
	(11, 'Prove su barre da c.a. B450 nuovo', NULL, 'CertificatoBarreB450_2010.prn', 'AcciaioCAB450_2010.prn', 'TrazionePiegamentoBarreB450_2010', 'Trazione barre', 'Piegamento barre', NULL, 'Diametro(mm)', NULL, 'Lunghezza(cm)', NULL, NULL, NULL, 6, 0, 11, 0, 'Verbali.prn'),
	(12, 'Prove su cubi D.M. 2008', NULL, 'CertificatoCubi2010.prn', 'Cubetti2010.prn', 'CompressioneCubiDM2008', 'Compressione su cubi', NULL, NULL, 'Lunghezza(mm)', 150, 'Larghezza(mm)', 150, 'Altezza(mm)', 150, 6, 28, 12, 0, 'Verbali.prn'),
	(13, 'Prove su barre Centro Trasformazione', NULL, 'CertificatoBarreCT.prn', 'AcciaioCT.prn', 'TrazionePiegamentoBarreCT', 'Trazione barre', 'Piegamento barre', NULL, 'Diametro(mm)', NULL, 'Lunghezza(cm)', NULL, NULL, NULL, 6, 0, 13, 0, 'VerbaleCT.prn'),
	(14, 'Prove di trazione su profilati in acciaio 2011', NULL, 'CertificatoTrazioneProfilati2011.prn', 'MinutaTrazioneProfilati2011.prn', 'TrazioneProfilati2011', 'Trazione su profilati', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 6, 0, 14, 0, 'Verbali.prn'),
	(15, 'Prove su reti elettrosaldate 2011', NULL, 'CertificatoReti2011.prn', 'MinutaReti2011.prn', 'TrazioneReti2011', 'Trazione su reti', 'Distacco sul nodo', NULL, 'Diametro(mm)', NULL, NULL, NULL, NULL, NULL, 6, 0, 15, 0, 'Verbali.prn'),
	(16, 'Prove su cubi D.M. 2018', NULL, 'CertificatoCubi2018.prn', 'Cubetti2018.prn', 'CompressioneCubiDM2018', 'Compressione su cubi', NULL, NULL, 'Lunghezza(mm)', 150, 'Larghezza(mm)', 150, 'Altezza(mm)', 150, 6, 28, 12, 0, 'Verbali.prn');
/*!40000 ALTER TABLE `tipi_certificato` ENABLE KEYS */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;

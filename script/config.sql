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


-- Dump della struttura di tabella winsigma.configurazione
CREATE TABLE IF NOT EXISTS `configurazione` (
  `Nome` varchar(50) NOT NULL,
  `Valore` varchar(500) NOT NULL,
  `Descrizione` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`Nome`),
  UNIQUE KEY `Nome` (`Nome`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dump dei dati della tabella winsigma.configurazione: ~31 rows (circa)
/*!40000 ALTER TABLE `configurazione` DISABLE KEYS */;
INSERT INTO `configurazione` (`Nome`, `Valore`, `Descrizione`) VALUES
	('AliquotaIVA', '22', 'Aliquota IVA corrente in percentuale'),
	('CAP', '50013', NULL),
	('CapitaleSociale', '1000.00', NULL),
	('CodiceFiscaleEmittente', '04530950486', 'Codice Fiscale soggetto emittente (InfoSvil Srl)'),
	('Comune', 'CAMPI BISENZIO', NULL),
	('Denominazione', 'LABORATORIO SIGMA SRL', 'Denominazione azienda (cedente/prestatore)'),
	('DenominazioneEmittente', 'INFOSVIL SRL', 'Denominazione soggetto emittente (InfoSvil Srl)'),
	('Divisa', 'EUR', 'Divisa/valuta corrente'),
	('EstensioneXML', 'xml', NULL),
	('IdCodiceEmittente', '04530950486', 'Partita IVA soggetto emittente (InfoSvil Srl)'),
	('IdCodiceTrasmittente', '04530950486', 'Partita IVA soggetto tramittente (InfoSvil Srl)'),
	('IdPaese', 'IT', NULL),
	('Indirizzo', 'VIA PIERO GOBETTI', NULL),
	('Nazione', 'IT', NULL),
	('NumeroCivico', '8', NULL),
	('NumeroREA', '240940', NULL),
	('PartitaIVA', '00667530489', 'Partita IVA (cedente/prestatore)'),
	('ProgressivoXML', '00031', 'Progressivo dell\'ultima esportazione XML effettuata'),
	('Provincia', 'FI', NULL),
	('RegimeFiscale', 'RF01', 'Regime fiscale (cedente/prestatore)'),
	('SocioUnico', 'SM', NULL),
	('SoggettoEmittente', 'TZ', 'CC: fattura compilata da cessionario/committente (il cliente) TZ: fattura compilata da soggetto terzo'),
	('StatoLiquidazione', 'LN', NULL),
	('TipoDocFattura', 'TD01', NULL),
	('TipoDocNotaCredito', 'TD04', NULL),
	('TipologiaFileXML', 'DF', NULL),
	('UfficioREA', 'FI', NULL),
	('VersionePA', 'FPA12', 'Formato trasmissione fattura Pubblica Amministrazione'),
	('VersionePR', 'FPR12', 'Formato trasmissione fattura soggetto privato'),
	('XMLFolder', 'C:\\is\\dati', NULL),
	('XMLHeader', '<?xml version="1.0" encoding="UTF-8"?>\n<p:FatturaElettronica versione="%s" xmlns:ds="http://www.w3.org/2000/09/xmldsig#"\nxmlns:p="http://ivaservizi.agenziaentrate.gov.it/docs/xsd/fatture/v1.2"\nxmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"\nxsi:schemaLocation="http://ivaservizi.agenziaentrate.gov.it/docs/xsd/fatture/v1.2 fatturaordinaria_v1.2.xsd">', 'Header file XML per trasmissione fatture');
/*!40000 ALTER TABLE `configurazione` ENABLE KEYS */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;

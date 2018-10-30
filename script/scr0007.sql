--------------------------------------------------
-- VERSIONE 4.7.0
--------------------------------------------------
-- tabella AZIENDE: aggiunta campi CodiceDestinatario e PEC
ALTER TABLE `AZIENDE`
	ADD COLUMN `CodiceDestinatario` VARCHAR(7) NULL DEFAULT NULL AFTER `UsaTuttiListini`,
	ADD COLUMN `PEC` VARCHAR(200) NULL DEFAULT NULL AFTER `CodiceDestinatario`;


	-- tabella FATTURE: aggiunta campi
ALTER TABLE `FATTURE`
--	ADD COLUMN `CodiceDestinatario` VARCHAR(7) NULL DEFAULT NULL AFTER `fElett`,
	ADD COLUMN `PEC` VARCHAR(200) NULL DEFAULT NULL AFTER `CodiceDestinatario`,
	ADD COLUMN `CUP` VARCHAR(20) NULL DEFAULT NULL AFTER `PEC`,
	ADD COLUMN `CIG` VARCHAR(20) NULL DEFAULT NULL AFTER `CUP`,
	ADD COLUMN `OrdineAcquisto` VARCHAR(200) NULL DEFAULT NULL AFTER `CIG`,
	ADD COLUMN `DataOrdineAcquisto` DATE NULL DEFAULT NULL AFTER `OrdineAcquisto`,
	ADD COLUMN `Contratto` VARCHAR(200) NULL DEFAULT NULL AFTER `DataOrdineAcquisto`,
	ADD COLUMN `DataContratto` DATE NULL DEFAULT NULL AFTER `Contratto`,
	ADD COLUMN `NumeroDDT` VARCHAR(20) NULL DEFAULT NULL AFTER `DataContratto`,
	ADD COLUMN `DataDDT` DATE NULL DEFAULT NULL AFTER `NumeroDDT`;


-- tabella TIPI_PAGAMENTO: aggiunta campo codifica XML
ALTER TABLE `TIPI_PAGAMENTO`
	ADD COLUMN `CodiceXML` VARCHAR(4) NULL DEFAULT NULL AFTER `NumeroConto`;
	
-- creazione tabella CONFIGURAZIONE
CREATE TABLE IF NOT EXISTS `CONFIGURAZIONE` (
  `Nome` varchar(50) NOT NULL,
  `Valore` varchar(500) NOT NULL,
  `Descrizione` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`Nome`),
  UNIQUE KEY `Nome` (`Nome`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dump dei dati della tabella winsigma.configurazione: ~31 rows (circa)
/*!40000 ALTER TABLE `configurazione` DISABLE KEYS */;
INSERT INTO `CONFIGURAZIONE` (`Nome`, `Valore`, `Descrizione`) VALUES
	('AliquotaIVA', '22', 'Aliquota IVA corrente in percentuale'),
	('CAP', '50013', NULL),
	('CapitaleSociale', '0.00', NULL),
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
	('ProgressivoXML', '00001', 'Progressivo dell\'ultima esportazione XML effettuata'),
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

	
DROP TABLE IF EXISTS `TIPI_PAGAMENTO`;
	CREATE TABLE IF NOT EXISTS `TIPI_PAGAMENTO` (
  `Codice` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `VecchioCod` smallint(6) DEFAULT NULL,
  `Nome` varchar(32) DEFAULT NULL,
  `Descrizione` varchar(250) DEFAULT NULL,
  `Allineamento` smallint(6) DEFAULT NULL,
  `NumRate` smallint(6) DEFAULT NULL,
  `GiorniPrimaScad` smallint(6) DEFAULT NULL,
  `Banca` varchar(64) DEFAULT NULL,
  `ABI` varchar(8) DEFAULT NULL,
  `CAB` varchar(8) DEFAULT NULL,
  `CIN` varchar(8) DEFAULT NULL,
  `NumeroConto` varchar(32) DEFAULT NULL,
  `CodiceXML` varchar(4) DEFAULT NULL,
  PRIMARY KEY (`Codice`)
) ENGINE=MyISAM AUTO_INCREMENT=71 DEFAULT CHARSET=latin1;

-- Tabella TIPI_PAGAMENTO: 69 rows
INSERT INTO `TIPI_PAGAMENTO` (`Codice`, `VecchioCod`, `Nome`, `Descrizione`, `Allineamento`, `NumRate`, `GiorniPrimaScad`, `Banca`, `ABI`, `CAB`, `CIN`, `NumeroConto`, `CodiceXML`) VALUES
	(1, 10, 'R.B. 30 GG FM + 5 GG', 'R.B. 30 GG FM + 5 GG', 205, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(2, 20, 'R.B. 60 GG FM + 5 GG', 'R.B. 60 GG FM + 5 GG', 205, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(3, 11, 'R.B. 30 GG F.M.', 'R.B. 30 GG FINE MESE', 200, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(4, 21, 'R.B. 60 GG F.M.', 'R.B. 60 GG FINE MESE', 200, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(5, 30, 'R.B. 90 GG D.F.', 'R.B. 90 GG DATA FT', 250, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(6, 31, 'R.B. 90 GG F.M.', 'R.B. 90 GG FINE MESE', 200, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(7, 40, 'RIM. DIR. D.R. O D.F.', 'VS. RIMESSA DIRETTA A RIC. O FT', 50, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(8, 41, 'RIM. DIR. 30 GG D.F.', 'VS. RIMESSA DIRETTA A 30 GG D.F.', 50, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(9, 2, 'CONTRASSEGNO', 'CONTRASSEGNO', 50, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(10, 42, 'RIM. DIR. 60 GG D.F.', 'VS. RIM. DIRETTA A 60 GG D.F.', 50, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(11, 43, 'RIM. DIR. 90 GG D.F.', 'VS. RIM. DIRETTA A 90 GG D.F.', 50, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(12, 44, 'RIM. DIR. 120 GG D.F.', 'VS. RIM. DIRETTA A 120 GG D.F.', 50, 1, 120, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(13, 45, 'ANTICIPATO', 'ANTICIPATO', 50, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(14, 12, 'R.B. 30/60 GG D.F.', 'R.B. 30/60 GG. D.F.', 250, 2, 30, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(15, 13, 'R.B. 30/60 GG F.M.', 'R.B. 30/60 GG. FINE MESE', 200, 2, 30, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(16, 46, 'BON. BANC. 30 GG D.F.', 'VS. BONIF. BANCARIO A 30 GG D.F.', 150, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(17, 47, 'BON. BANC. 60 GG D.F.', 'VS. BONIF. BANCARIO A 60 GG D.F.', 150, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(18, 60, 'IMP. UNITO R.B. E D.F.', 'IMPORTO UNITO ALLA RB DELLA FT', 50, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(19, 61, 'CON CESSIONI', 'CON CESSIONI', 50, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP00'),
	(20, 48, 'BON. BANC. 30 GG F.M.', 'VS. BONIF. BANCARIO A 30 GG F.M.', 100, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(21, 14, 'R.B. 60 GG F.M.+ 10 GG MESE SUCC', 'R.B. 60 GG F.M.+10 GG MESE SUCCESSIVO', 210, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(22, 15, 'R.B. 30/60/90 GG F.M.', 'R.B. 30/60/90 GG F.M.', 200, 3, 30, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(23, 17, 'R.B. 90 gg f.m. + 10', 'R.B. 90 gg f.m.+ 10 ', 210, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(24, 49, 'RIM. DIR. 90 GG F.M.', 'VS. RIMESSA DIRETTA 90 GG F.M.', 0, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(25, 32, 'R.B. 120 GG D.F.', 'R.B. 120 GG D.F.', 250, 1, 120, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(26, 33, 'R.B. 120 GG F.M.', 'R.B. 120 GG FINE MESE', 200, 1, 120, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(27, 50, 'BONIFICO BANCARIO 90 GG D.F.', NULL, 150, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(28, 51, 'BON. BANC. 60 GG F.M.', 'VS BONIF. BANCARIO A 60 GG F.M.', 100, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(29, 22, 'RIM. DIR. 60 GG F.M. D.F.', 'VS RIM. DIRETTA 60 GG F.M.D.F.', 0, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(30, 52, 'BON. BANC. 90 GG F.M.', 'VS. BONIFICO BANCARIO 90 GG F.M.', 100, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(31, 70, 'RIM. DIR. 30 GG F.M.', 'VS RIMESSA DIRETTA 30 GG F.M.', 0, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(32, 71, 'RIM. DIR. 60 GG F.M.', 'VS RIMESSA DIRETTA 60 GG F.M.', 0, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(33, 72, 'RIM. DIR. 90 GG F.M.', 'VS RIMESSA DIRETTA 90 GG F.M.', 0, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(34, 73, 'RIM. DIR. 120 GG F.M.', 'VS RIMESSA DIRETTA 120 GG F.M.', 0, 1, 120, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(35, 53, 'RIM. DIR. 60 GG F.M.', 'RIMESSA DIRETTA 60 GG F.M.', 0, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(36, 55, 'BON. BANC. D.R. D.F', 'VS. BONIFICO BANCARIO RIC. FT.', 150, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(37, 91, 'RITIRO CERTIFICATI', 'AL RITIRO DEI CERTIFICATI', 50, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(38, 18, 'R.B. 90/120 GG D.F.', 'R.B. 90/120 GG D.F.', 250, 2, 90, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(39, 54, 'BON. BANC. 120 GG F.M.', 'VS. BONIFICO BANCARIO 120 GG F.M.', 100, 1, 120, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(40, 88, 'BOLLETTINO C/C POSTALE', 'BOLLETTINO C/C POSTALE', 50, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP18'),
	(41, 56, 'BON. BANC. 60/90/120 GG D.F.', 'BON. BANCARIO 60/90/120 GG D.F.', 150, 3, 60, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(42, 57, 'BON. BANC. 90/120 GG F.M.', 'VS. BONIF BANCARIO 90/120 GG F.M.', 100, 2, 120, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(43, 16, 'R.B. 60/90 GG F.M.', 'R.B. 60/90 GG F.M.', 200, 2, 60, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(44, 90, 'EFFETTO CAMBIARIO', 'EFFETTO CAMBIARIO', 50, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP06'),
	(45, 58, 'BONIFICO BANCARIO', 'VS. BONIFICO BANCARIO', 150, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(46, 67, 'R.B. 30 + 10 GG D.F. F.M.', NULL, 210, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(47, 65, 'R.B.30 GG.F.M. AL 15 MESE SUCCES', NULL, 215, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(48, 66, 'R.B. 90 GG F.M. AL 5 MESE SUCCES', NULL, 205, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(49, 55, 'BON. BANC. 30/60 GG  F.M.', 'BONIFICO BANCARIO 30/60 GG F.M.', 100, 2, 30, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(50, 54, 'BON.BANC.120 GG D.F.', 'VS. BONIFICO BANCARIO 120 G.G. D.F.', 150, 1, 120, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(51, 0, 'BON. BANC. 30 GG F.M. + 10 GG', 'VS. BONIFICO BANCARIO 30 GG F.M. + 10 GG', 110, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(52, 0, 'RI.BA 60/90 GG + 5 GG', NULL, 205, 2, 60, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(53, 55, 'BONIFICO BANCARIO 30/60/ GG F.M.', 'BONIFICO BANCARIO 30/60/90 GG F.M.', 100, 2, 30, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(54, 55, 'BONIF.BANCARIO 30/60/90 GG F.M.', 'BONIFICO BANCARIO 30/60/90 GG F.M.', 100, 3, 30, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(55, 56, 'BONIFICO BANCARIO 60/90 GG F.M.', 'BONIFICO BANCARIO 60/90 GG F.M.', 100, 2, 60, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(57, 92, 'PAGAMENTO EFFETTUATO', NULL, 50, 0, 0, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(58, 10, 'RB 30 GG FM + 2GG', 'R.B. 30 GG F.M. + 2GG', 5, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(59, 20, 'R.B.60 GG FM + 15 GG', 'R.B.60 GG FM + 15 GG', 215, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(60, 0, 'BON.BANC. 30 GG F.M. + 10 GG', 'VS BONIFICO BANCARIO 30 GG FM + 10 gg', 10, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(61, 11, 'RI.BA. 60 GG D.F. F.M.', 'RI.BA. 60 GG D.F. F.M.', 200, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(62, 0, 'BON. BANC. 30 GG F.M. + 15 GG', 'BONIFICO BANCARIO 30 GG F.M. + 15 GG', 115, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(63, 12, 'RI.BA. 30 GG D.F.', NULL, 250, 1, 30, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(64, 65, 'R.B. 90 GG F.M. + 15 GG', 'R.B. 90 GG F.M. + 15 GG', 15, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(65, 18, 'R.B. 90/120 GG. F.M.', 'R.B. 90/120 GG D.F.', 200, 2, 90, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(66, 0, 'R.B. 60/90 GG +10 GG', NULL, 210, 2, 60, NULL, NULL, NULL, NULL, NULL, 'MP12'),
	(67, 0, 'BON. BANC. 60 GG F.M. + 10 GG', 'BONIFICO BANCARIO 60 GG F.M. + 15 GG', 110, 1, 60, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(68, 43, 'RIM. DIR. 180 GG D.F.', 'VS RIMESSA DIRETTA 180 GG D.F.', 50, 1, 180, NULL, NULL, NULL, NULL, NULL, 'MP01'),
	(69, 0, 'BON. BANC. 90 GG F.M. + 10 GG', 'BON. BANC. 90 GG F.M. + 10 GG', 100, 1, 90, NULL, NULL, NULL, NULL, NULL, 'MP05'),
	(70, 58, 'BONIFICO VISTA FATTURA', 'BONIFICO VISTA FATTURA', 50, 1, 0, NULL, NULL, NULL, NULL, NULL, 'MP05');

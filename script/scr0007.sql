--------------------------------------------------
-- VERSIONE 4.7.0
--------------------------------------------------
-- tabella AZIENDE: aggiunta campi CodiceDestinatario e PEC
ALTER TABLE `aziende`
	ADD COLUMN `CodiceDestinatario` VARCHAR(7) NULL DEFAULT NULL AFTER `UsaTuttiListini`,
	ADD COLUMN `PEC` VARCHAR(200) NULL DEFAULT NULL AFTER `CodiceDestinatario`;


	-- tabella FATTURE: aggiunta campi
ALTER TABLE `fatture`
	ADD COLUMN `CodiceDestinatario` VARCHAR(7) NULL DEFAULT NULL AFTER `fElett`,
	ADD COLUMN `PEC` VARCHAR(200) NULL DEFAULT NULL AFTER `CodiceDestinatario`;
	ADD COLUMN `CUP` VARCHAR(20) NULL DEFAULT NULL AFTER `PEC`,
	ADD COLUMN `CIG` VARCHAR(20) NULL DEFAULT NULL AFTER `CUP`,
	ADD COLUMN `OrdineAcquisto` VARCHAR(20) NULL DEFAULT NULL AFTER `CIG`,
	ADD COLUMN `DataOrdineAcquisto` DATE NULL DEFAULT NULL AFTER `OrdineAcquisto`,
	ADD COLUMN `Contratto` VARCHAR(20) NULL DEFAULT NULL AFTER `DataOrdineAcquisto`,
	ADD COLUMN `DataContratto` DATE NULL DEFAULT NULL AFTER `Contratto`,
	ADD COLUMN `NumeroDDT` VARCHAR(20) NULL DEFAULT NULL AFTER `DataContratto`,
	ADD COLUMN `DataDDT` DATE NULL DEFAULT NULL AFTER `NumeroDDT`;


-- creazione tabella CONFIGURAZIONE
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

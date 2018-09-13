--------------------------------------------------
-- VERSIONE 4.7.0
--------------------------------------------------
-- tabella AZIENDE: aggiunta campi CodiceDestinatario e PEC
ALTER TABLE `aziende`
	ADD COLUMN `CodiceDestinatario` VARCHAR(7) NULL DEFAULT NULL AFTER `UsaTuttiListini`,
	ADD COLUMN `PEC` VARCHAR(200) NULL DEFAULT NULL AFTER `CodiceDestinatario`;


-- creazione tabella CONFIGURAZIONE
CREATE TABLE IF NOT EXISTS `configurazione` (
  `Nome` varchar(50) NOT NULL,
  `Valore` varchar(500) NOT NULL,
  `Descrizione` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`Nome`),
  UNIQUE KEY `Nome` (`Nome`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- inserimento dati tabella CONFIGURAZIONE
/*!40000 ALTER TABLE `configurazione` DISABLE KEYS */;
INSERT INTO `configurazione` (`Nome`, `Valore`, `Descrizione`) VALUES
	('AliquotaIVA', '22', 'Aliquota IVA corrente in percentuale'),
	('CodiceFiscaleEmittente', '04530950486', 'Codice Fiscale soggetto emittente (InfoSvil Srl)'),
	('DenominazioneEmittente', 'InfoSvil srl', 'Denominazione soggetto emittente (InfoSvil Srl)'),
	('EstensioneXML', 'xml', NULL),
	('IdCodiceEmittente', '04530950486', 'Partita IVA soggetto emittente (InfoSvil Srl)'),
	('IdCodiceTrasmittente', '04530950486', 'Partita IVA soggetto tramittente (InfoSvil Srl)'),
	('IdPaese', 'IT', NULL),
	('ProgressivoXML', '12376', NULL),
	('SoggettoEmittente', 'TZ', 'CC: fattura compilata da cessionario/committente (il cliente) TZ: fattura compilata da soggetto terzo'),
	('TipologiaFileXML', 'DF', NULL),
	('VersionePA', 'FPA12', 'Formato trasmissione fattura Pubblica Amministrazione'),
	('VersionePR', 'FPR12', 'Formato trasmissione fattura soggetto privato'),
	('XMLFolder', 'C:\\is\\dati', NULL),
	('XMLHeader', '<?xml version="1.0" encoding="UTF-8"?>\n<p:FatturaElettronica versione="%s" xmlns:ds="http://www.w3.org/2000/09/xmldsig#"\nxmlns:p="http://ivaservizi.agenziaentrate.gov.it/docs/xsd/fatture/v1.2"\nxmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"\nxsi:schemaLocation="http://ivaservizi.agenziaentrate.gov.it/docs/xsd/fatture/v1.2 fatturaordinaria_v1.2.xsd">', 'Header file XML per trasmissione fatture');

	
	
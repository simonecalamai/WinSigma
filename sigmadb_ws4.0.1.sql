SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

CREATE SCHEMA IF NOT EXISTS `WinSigma` DEFAULT CHARACTER SET latin1 ;
USE `WinSigma`;

-- -----------------------------------------------------
-- Table `WinSigma`.`AZIENDE`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`AZIENDE` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `TipoPagamento` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Privato` TINYINT(4) NULL DEFAULT NULL ,
  `ID` VARCHAR(8) NULL DEFAULT NULL ,
  `P_IVA` VARCHAR(16) NULL DEFAULT NULL ,
  `CodiceFiscale` VARCHAR(16) NULL DEFAULT NULL ,
  `RagioneSociale` VARCHAR(64) NULL DEFAULT NULL ,
  `RagioneSociale_Sped` VARCHAR(64) NULL DEFAULT NULL ,
  `Nome` VARCHAR(32) NULL DEFAULT NULL ,
  `Cognome` VARCHAR(32) NULL DEFAULT NULL ,
  `Indirizzo` VARCHAR(32) NULL DEFAULT NULL ,
  `CAP` VARCHAR(8) NULL DEFAULT NULL ,
  `Citta` VARCHAR(32) NULL DEFAULT NULL ,
  `Provincia` VARCHAR(4) NULL DEFAULT NULL ,
  `Indirizzo_Sped` VARCHAR(64) NULL DEFAULT NULL ,
  `CAP_Sped` VARCHAR(8) NULL DEFAULT NULL ,
  `Citta_Sped` VARCHAR(32) NULL DEFAULT NULL ,
  `Provincia_Sped` VARCHAR(4) NULL DEFAULT NULL ,
  `E_Mail` VARCHAR(32) NULL DEFAULT NULL ,
  `Telefono` VARCHAR(32) NULL DEFAULT NULL ,
  `Cellulare` VARCHAR(32) NULL DEFAULT NULL ,
  `Fax` VARCHAR(32) NULL DEFAULT NULL ,
  `Banca` VARCHAR(64) NULL DEFAULT NULL ,
  `ABI` VARCHAR(8) NULL DEFAULT NULL ,
  `CAB` VARCHAR(8) NULL DEFAULT NULL ,
  `Note` TEXT NULL DEFAULT NULL ,
  `Sconto` DOUBLE NULL DEFAULT NULL ,
  `DataInserimento` DATE NULL DEFAULT NULL ,
  `DataUltimoRapporto` DATE NULL DEFAULT NULL ,
  `IsImportante` TINYINT(4) NULL DEFAULT NULL ,
  `UsaTuttiListini` TINYINT(4) NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) ,
  INDEX `ID` (`ID` ASC, `P_IVA` ASC) ,
  INDEX `P_IVA` (`P_IVA` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 10901
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`AZIENDE_VECCHIE`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`AZIENDE_VECCHIE` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `TipoPagamento` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Privato` TINYINT(4) NULL DEFAULT NULL ,
  `ID` VARCHAR(8) NULL DEFAULT NULL ,
  `P_IVA` VARCHAR(16) NULL DEFAULT NULL ,
  `CodiceFiscale` VARCHAR(16) NULL DEFAULT NULL ,
  `RagioneSociale` VARCHAR(64) NULL DEFAULT NULL ,
  `RagioneSociale_Sped` VARCHAR(64) NULL DEFAULT NULL ,
  `Nome` VARCHAR(32) NULL DEFAULT NULL ,
  `Cognome` VARCHAR(32) NULL DEFAULT NULL ,
  `Indirizzo` VARCHAR(32) NULL DEFAULT NULL ,
  `CAP` VARCHAR(8) NULL DEFAULT NULL ,
  `Citta` VARCHAR(32) NULL DEFAULT NULL ,
  `Provincia` VARCHAR(4) NULL DEFAULT NULL ,
  `Indirizzo_Sped` VARCHAR(32) NULL DEFAULT NULL ,
  `CAP_Sped` VARCHAR(8) NULL DEFAULT NULL ,
  `Citta_Sped` VARCHAR(32) NULL DEFAULT NULL ,
  `Provincia_Sped` VARCHAR(4) NULL DEFAULT NULL ,
  `E_Mail` VARCHAR(32) NULL DEFAULT NULL ,
  `Telefono` VARCHAR(32) NULL DEFAULT NULL ,
  `Cellulare` VARCHAR(32) NULL DEFAULT NULL ,
  `Fax` VARCHAR(32) NULL DEFAULT NULL ,
  `Banca` VARCHAR(64) NULL DEFAULT NULL ,
  `ABI` VARCHAR(8) NULL DEFAULT NULL ,
  `CAB` VARCHAR(8) NULL DEFAULT NULL ,
  `Note` TEXT NULL DEFAULT NULL ,
  `Sconto` DOUBLE NULL DEFAULT NULL ,
  `DataInserimento` DATE NULL DEFAULT NULL ,
  `DataUltimoRapporto` DATE NULL DEFAULT NULL ,
  `IsImportante` TINYINT(4) NULL DEFAULT NULL ,
  `UsaTuttiListini` TINYINT(4) NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) )
ENGINE = MyISAM
AUTO_INCREMENT = 12027
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`CATEGORIE`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`CATEGORIE` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `ID` VARCHAR(8) NULL DEFAULT NULL ,
  `Nome` VARCHAR(64) NULL DEFAULT NULL ,
  `Descrizione` VARCHAR(128) NULL DEFAULT NULL ,
  `Listino` INT(10) UNSIGNED NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) ,
  UNIQUE INDEX `ID` (`ID` ASC, `Listino` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 440
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`CERTIFICATI`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`CERTIFICATI` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Verbale` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `TipoCertificato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `NumeroCertificato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Posizione` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Sperimentatore` VARCHAR(32) NULL DEFAULT NULL ,
  `Macchina` VARCHAR(64) NULL DEFAULT NULL ,
  `DataEmissione` DATE NULL DEFAULT NULL ,
  `DataProve` DATE NULL DEFAULT NULL ,
  `DataStampa` DATE NULL DEFAULT NULL ,
  `NumeroPagine` TINYINT(4) NULL DEFAULT NULL ,
  `EmendaIl` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `EmendatoDa` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Aderenza` TINYINT(1) NULL DEFAULT '0' ,
  PRIMARY KEY (`Codice`) ,
  INDEX `V` (`Verbale` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 65677
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`FATTURE`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`FATTURE` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Intestatario` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `TipoPagamento` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Numero` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Data` DATE NULL DEFAULT NULL ,
  `Scadenza` DATE NULL DEFAULT NULL ,
  `P_IVA` VARCHAR(16) NULL DEFAULT NULL ,
  `CodiceFiscale` VARCHAR(16) NULL DEFAULT NULL ,
  `RagioneSociale` VARCHAR(64) NULL DEFAULT NULL ,
  `IDIntestario` VARCHAR(8) NULL DEFAULT NULL ,
  `Indirizzo` VARCHAR(32) NULL DEFAULT NULL ,
  `CAP` VARCHAR(8) NULL DEFAULT NULL ,
  `Citta` VARCHAR(32) NULL DEFAULT NULL ,
  `Provincia` VARCHAR(4) NULL DEFAULT NULL ,
  `Banca` VARCHAR(64) NULL DEFAULT NULL ,
  `ABI` VARCHAR(8) NULL DEFAULT NULL ,
  `CAB` VARCHAR(8) NULL DEFAULT NULL ,
  `Sconto` DOUBLE NULL DEFAULT NULL ,
  `Note` TEXT NULL DEFAULT NULL ,
  `AliquotaIVA` DOUBLE NULL DEFAULT '20' ,
  `Spese` DOUBLE NULL DEFAULT '0' ,
  `Imponibile` DOUBLE NULL DEFAULT '0' ,
  `Archiviata` TINYINT(4) NULL DEFAULT '0' ,
  `Pagamento` VARCHAR(64) NULL DEFAULT NULL ,
  `TipoDocumento` TINYINT(4) NULL DEFAULT '0' ,
  `InUso` VARCHAR(64) NULL DEFAULT NULL ,
  `BancaAppoggio` VARCHAR(64) NULL DEFAULT NULL ,
  `ABIAppoggio` VARCHAR(8) NULL DEFAULT NULL ,
  `CABAppoggio` VARCHAR(8) NULL DEFAULT NULL ,
  `CINAppoggio` VARCHAR(8) NULL DEFAULT NULL ,
  `ContoAppoggio` VARCHAR(32) NULL DEFAULT NULL ,
  `RitenutaAcconto` DOUBLE NULL DEFAULT '0' ,
  PRIMARY KEY (`Codice`) ,
  INDEX `I` (`Intestatario` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 16478
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`LISTINI`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`LISTINI` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Azienda` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Nome` VARCHAR(32) NULL DEFAULT NULL ,
  `Autore` VARCHAR(16) NULL DEFAULT NULL ,
  `Inizio` DATE NULL DEFAULT NULL ,
  `Fine` DATE NULL DEFAULT NULL ,
  `CertOgniSerie` TINYINT(4) NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) )
ENGINE = MyISAM
AUTO_INCREMENT = 21
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`LOCALITA`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`LOCALITA` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Provincia` VARCHAR(100) NULL DEFAULT '' ,
  `Localita` VARCHAR(100) NULL DEFAULT '' ,
  `CAP` INT(11) NULL DEFAULT '0' ,
  `Indirizzo` VARCHAR(100) NULL DEFAULT '' ,
  `Tipologia` VARCHAR(64) NULL DEFAULT '' ,
  `Note` VARCHAR(64) NULL DEFAULT '' ,
  PRIMARY KEY (`Codice`) )
ENGINE = MyISAM
AUTO_INCREMENT = 17315
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`LOG`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`LOG` (
  `LOG_ID` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `LOG_EVENT_DESCRIPTION` VARCHAR(100) NULL DEFAULT NULL ,
  PRIMARY KEY (`LOG_ID`) )
ENGINE = MyISAM
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`MARCHI`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`MARCHI` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Nome` VARCHAR(32) NULL DEFAULT NULL ,
  `Descrizione` VARCHAR(250) NULL DEFAULT NULL ,
  `Produttore` VARCHAR(64) NULL DEFAULT NULL ,
  `Stabilimento` VARCHAR(64) NULL DEFAULT NULL ,
  `Immagine` BLOB NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) ,
  UNIQUE INDEX `Nome` (`Nome` ASC) ,
  UNIQUE INDEX `Nome_2` (`Nome` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 186
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`OPERATORI`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`OPERATORI` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Nome` VARCHAR(32) NULL DEFAULT NULL ,
  `Cognome` VARCHAR(32) NULL DEFAULT NULL ,
  `Password` VARCHAR(32) NULL DEFAULT NULL ,
  `Privilegi` INT(11) NULL DEFAULT NULL ,
  `Sperimentatore` SMALLINT(6) NULL DEFAULT NULL ,
  `Macchina` VARCHAR(64) NULL DEFAULT NULL ,
  `Inizio` DATE NULL DEFAULT NULL ,
  `Fine` DATE NULL DEFAULT NULL ,
  `Sospeso` SMALLINT(6) NULL DEFAULT NULL ,
  `Titolo` VARCHAR(16) NULL DEFAULT NULL ,
  `Responsabile` TINYINT(4) NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) ,
  UNIQUE INDEX `Cognome` (`Cognome` ASC, `Nome` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 17
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`OPERAZIONI`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`OPERAZIONI` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `TipoOperazione` VARCHAR(32) NULL DEFAULT NULL ,
  `TipoDocumento` VARCHAR(32) NULL DEFAULT NULL ,
  `DocumentoSostituito` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `CertificatoEmendato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Operatore` INT(10) UNSIGNED NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) )
ENGINE = MyISAM
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`PROVINI`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`PROVINI` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Serie` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `DataInserimento` DATE NULL DEFAULT NULL ,
  `Collaudatore` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Servizio` VARCHAR(8) NULL DEFAULT NULL ,
  `Risultati` BLOB NULL DEFAULT NULL ,
  `InUso` VARCHAR(64) NULL DEFAULT NULL ,
  `Marchio` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `RotoliCT` TINYINT(1) NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) ,
  INDEX `S` (`Serie` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 265984
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`SERIE`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`SERIE` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Verbale` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `TipoCertificato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `NumeroProvini` SMALLINT(5) UNSIGNED NULL DEFAULT NULL ,
  `NuovoCertificato` TINYINT(4) NULL DEFAULT NULL ,
  `Certificato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `DataPrelievo` DATE NULL DEFAULT NULL ,
  `Dataprova` DATE NULL DEFAULT NULL ,
  `StrutturaPrelievo` VARCHAR(64) NULL DEFAULT NULL ,
  `Sigla` VARCHAR(8) NULL DEFAULT NULL ,
  `Materiale` VARCHAR(80) NULL DEFAULT NULL ,
  `Snervamento` DOUBLE NULL DEFAULT NULL ,
  `Servizio1` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Servizio2` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Servizio3` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Servizio4` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Servizio5` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Servizio6` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `ServAggiungibile` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `ServAggiunto` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Sperimentatore` VARCHAR(32) NULL DEFAULT NULL ,
  `Macchina` VARCHAR(64) NULL DEFAULT NULL ,
  `Osservazioni` VARCHAR(255) NULL DEFAULT NULL ,
  `TipoProva` SMALLINT(5) UNSIGNED NULL DEFAULT NULL ,
  `Dimensione1` DOUBLE NULL DEFAULT NULL ,
  `Dimensione2` DOUBLE NULL DEFAULT NULL ,
  `Dimensione3` DOUBLE NULL DEFAULT NULL ,
  `Marchio` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `DataND` VARCHAR(16) NULL DEFAULT NULL ,
  `IDMateriale` VARCHAR(8) NULL DEFAULT NULL ,
  `Checked` TINYINT(4) NULL DEFAULT '0' ,
  `Ordinamento` INT(11) NULL DEFAULT '0' ,
  `VerbalePrelievo` VARCHAR(64) NULL DEFAULT NULL ,
  `SiglaFornitore` VARCHAR(128) NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) ,
  INDEX `V` (`Verbale` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 124219
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`SERVIZI_EROGATI`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`SERVIZI_EROGATI` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `CodiceServizio` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Verbale` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Fattura` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Serie` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Descrizione` VARCHAR(255) NULL DEFAULT NULL ,
  `ID_Listino` VARCHAR(8) NULL DEFAULT NULL ,
  `Quantita` DOUBLE NULL DEFAULT NULL ,
  `Prezzo` DOUBLE NULL DEFAULT NULL ,
  `Sconto` DOUBLE NULL DEFAULT NULL ,
  `Nome` VARCHAR(64) NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) ,
  INDEX `V` (`Verbale` ASC) ,
  INDEX `F` (`Fattura` ASC) ,
  INDEX `S` (`Serie` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 130836
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`SERVIZI_LISTINO`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`SERVIZI_LISTINO` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Certificato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Categoria` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `ID` VARCHAR(8) NULL DEFAULT NULL ,
  `Descrizione` VARCHAR(255) NULL DEFAULT NULL ,
  `Emissione` TINYINT(4) NULL DEFAULT NULL ,
  `Campioni` SMALLINT(5) UNSIGNED NULL DEFAULT NULL ,
  `Prove` SMALLINT(6) NULL DEFAULT NULL ,
  `PerSerie` TINYINT(4) NULL DEFAULT NULL ,
  `Prezzo` DOUBLE NULL DEFAULT NULL ,
  `Sconto` DOUBLE NULL DEFAULT NULL ,
  `Nome` VARCHAR(64) NULL DEFAULT NULL ,
  `Aggiuntivo` TINYINT(4) NULL DEFAULT NULL ,
  `Norma` VARCHAR(64) NULL DEFAULT NULL ,
  `Riferimenti` VARCHAR(32) NULL DEFAULT NULL ,
  `Concessione` TINYINT(4) NULL DEFAULT '0' ,
  `CommentoMateriale` TINYINT(4) NULL DEFAULT '0' ,
  `ProviniPerSerie` SMALLINT(5) NULL DEFAULT '0' ,
  `Commento` VARCHAR(64) NULL DEFAULT NULL ,
  `Certificato2` INT(11) NULL DEFAULT '0' ,
  `Prove2` SMALLINT(6) NULL DEFAULT '0' ,
  `Certificato3` INT(11) NULL DEFAULT '0' ,
  `Prove3` SMALLINT(6) NULL DEFAULT '0' ,
  `Certificato4` INT(11) NULL DEFAULT '0' ,
  `Prove4` SMALLINT(6) NULL DEFAULT '0' ,
  PRIMARY KEY (`Codice`) ,
  UNIQUE INDEX `ID` (`ID` ASC, `Categoria` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 8601
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`SERVIZI_STANDARD`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`SERVIZI_STANDARD` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `TipoCertificato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `ID1` VARCHAR(16) NULL DEFAULT NULL ,
  `ID2` VARCHAR(16) NULL DEFAULT NULL ,
  `ID3` VARCHAR(16) NULL DEFAULT NULL ,
  `ID4` VARCHAR(16) NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) )
ENGINE = MyISAM
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`TIPI_CERTIFICATO`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`TIPI_CERTIFICATO` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Nome` VARCHAR(64) NULL DEFAULT NULL ,
  `Descrizione` VARCHAR(64) NULL DEFAULT NULL ,
  `LayoutStampa` VARCHAR(40) NULL DEFAULT NULL ,
  `LayoutStampaMinuta` VARCHAR(40) NULL DEFAULT NULL ,
  `FinestraDialogo` VARCHAR(64) NULL DEFAULT NULL ,
  `ProvaA` VARCHAR(64) NULL DEFAULT NULL ,
  `ProvaB` VARCHAR(64) NULL DEFAULT NULL ,
  `ProvaC` VARCHAR(64) NULL DEFAULT NULL ,
  `Dimensione1` VARCHAR(32) NULL DEFAULT NULL ,
  `ValoreDim1` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Dimensione2` VARCHAR(32) NULL DEFAULT NULL ,
  `ValoreDim2` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Dimensione3` VARCHAR(32) NULL DEFAULT NULL ,
  `ValoreDim3` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `ProvXcertificato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Maturazione` INT(11) NULL DEFAULT '0' ,
  `Ordinamento` INT(11) NULL DEFAULT '0' ,
  `Variante` TINYINT(4) NULL DEFAULT '0' ,
  PRIMARY KEY (`Codice`) )
ENGINE = MyISAM
AUTO_INCREMENT = 14
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`TIPI_MATERIALE`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`TIPI_MATERIALE` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `ID` VARCHAR(8) NULL DEFAULT NULL ,
  `Nome` VARCHAR(32) NULL DEFAULT NULL ,
  `Descrizione` VARCHAR(250) NULL DEFAULT NULL ,
  `DiDefault` TINYINT(4) NULL DEFAULT NULL ,
  `TipoCertificato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `Snervamento` DOUBLE NULL DEFAULT NULL ,
  `TipoCertificato2` INT(11) NULL DEFAULT '0' ,
  `TipoCertificato3` INT(11) NULL DEFAULT '0' ,
  `TipoCertificato4` INT(11) NULL DEFAULT '0' ,
  PRIMARY KEY (`Codice`) ,
  UNIQUE INDEX `ID` (`ID` ASC) )
ENGINE = MyISAM
AUTO_INCREMENT = 232
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`TIPI_PAGAMENTO`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`TIPI_PAGAMENTO` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `VecchioCod` SMALLINT(6) NULL DEFAULT NULL ,
  `Nome` VARCHAR(32) NULL DEFAULT NULL ,
  `Descrizione` VARCHAR(250) NULL DEFAULT NULL ,
  `Allineamento` SMALLINT(6) NULL DEFAULT NULL ,
  `NumRate` SMALLINT(6) NULL DEFAULT NULL ,
  `GiorniPrimaScad` SMALLINT(6) NULL DEFAULT NULL ,
  `Banca` VARCHAR(64) NULL DEFAULT NULL ,
  `ABI` VARCHAR(8) NULL DEFAULT NULL ,
  `CAB` VARCHAR(8) NULL DEFAULT NULL ,
  `CIN` VARCHAR(8) NULL DEFAULT NULL ,
  `NumeroConto` VARCHAR(32) NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) )
ENGINE = MyISAM
AUTO_INCREMENT = 51
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`TIPI_SCONTO`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`TIPI_SCONTO` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `Soglia` INT(11) NULL DEFAULT NULL ,
  `RiduzioneSoglia` DOUBLE NULL DEFAULT NULL ,
  `Livello1` SMALLINT(6) NULL DEFAULT NULL ,
  `Riduzione1` DOUBLE NULL DEFAULT NULL ,
  `Livello2` SMALLINT(6) NULL DEFAULT NULL ,
  `Riduzione2` DOUBLE NULL DEFAULT NULL ,
  PRIMARY KEY (`Codice`) )
ENGINE = MyISAM
DEFAULT CHARACTER SET = latin1;


-- -----------------------------------------------------
-- Table `WinSigma`.`VERBALI`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `WinSigma`.`VERBALI` (
  `Codice` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT ,
  `TipoVerbale` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `LungaScadenza` TINYINT(4) NULL DEFAULT NULL ,
  `Fattura` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `InFatturazione` TINYINT(4) NULL DEFAULT NULL ,
  `IntestatarioCertificato` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `IntestatarioFattura` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `ImpresaRichiedente` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `ListinoGenerale` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `ListinoParticolare` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `NomeIntestatarioCertificato` VARCHAR(64) NULL DEFAULT NULL ,
  `NomeIntestatarioFattura` VARCHAR(64) NULL DEFAULT NULL ,
  `NomeImpresaRichiedente` VARCHAR(64) NULL DEFAULT NULL ,
  `IDIntestatarioCertificato` VARCHAR(8) NULL DEFAULT NULL ,
  `IDIntestatarioFattura` VARCHAR(8) NULL DEFAULT NULL ,
  `IDImpresaRichiedente` VARCHAR(8) NULL DEFAULT NULL ,
  `IndirizzoIntCertificato` VARCHAR(64) NULL DEFAULT NULL ,
  `IndirizzoIntFattura` VARCHAR(64) NULL DEFAULT NULL ,
  `Pagamento` VARCHAR(32) NULL DEFAULT NULL ,
  `P_IVA` VARCHAR(16) NULL DEFAULT NULL ,
  `IndirizzoImpresaRichiedente` VARCHAR(64) NULL DEFAULT NULL ,
  `ProgressivoTotale` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `ProgressivoParziale` INT(10) UNSIGNED NULL DEFAULT NULL ,
  `DirettoreLavori` VARCHAR(64) NULL DEFAULT NULL ,
  `DomandaSottoscritta` TINYINT(4) NULL DEFAULT NULL ,
  `Proprietario` VARCHAR(128) NULL DEFAULT NULL ,
  `Richiedente` VARCHAR(64) NULL DEFAULT NULL ,
  `Cantiere` VARCHAR(255) NULL DEFAULT NULL ,
  `DescrizioneProveRichieste` VARCHAR(255) NULL DEFAULT NULL ,
  `DescrizioneMateriale` VARCHAR(255) NULL DEFAULT NULL ,
  `NumLetteraIncarico` VARCHAR(64) NULL DEFAULT NULL ,
  `LetteraIncarico` TINYINT(4) NULL DEFAULT NULL ,
  `DataAccettazione` DATE NULL DEFAULT NULL ,
  `DataPrimaStampa` DATE NULL DEFAULT NULL ,
  `DataConsegna` DATE NULL DEFAULT NULL ,
  `OraConsegna` VARCHAR(16) NULL DEFAULT NULL ,
  `DataChiusura` DATE NULL DEFAULT NULL ,
  `CertOgniSerie` TINYINT(4) NULL DEFAULT NULL ,
  `VuoiUrgenza` TINYINT(4) NULL DEFAULT NULL ,
  `VuoiSpedizione` TINYINT(4) NULL DEFAULT NULL ,
  `Destinatario` VARCHAR(255) NULL DEFAULT NULL ,
  `NoteSpedizione` VARCHAR(255) NULL DEFAULT NULL ,
  `Operatore` VARCHAR(32) NULL DEFAULT NULL ,
  `InUso` VARCHAR(64) NULL DEFAULT NULL ,
  `Annullato` TINYINT(4) NULL DEFAULT '0' ,
  `CodFiscale` VARCHAR(16) NULL DEFAULT '0' ,
  PRIMARY KEY (`Codice`) )
ENGINE = MyISAM
AUTO_INCREMENT = 31764
DEFAULT CHARACTER SET = latin1;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

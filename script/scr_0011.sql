ALTER TABLE `FATTURE`
	ADD COLUMN `RipartizioneImponibile` VARCHAR(300) NULL DEFAULT NULL AFTER `CondizioniPagamento`;

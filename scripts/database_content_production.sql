--
-- ECHOES Alert database initialization
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

SET search_path = public, pg_catalog;

--
-- SEQUENCE SetVal
--

SELECT pg_catalog.setval('"T_ADDON_ADO_ADO_ID_seq"', 2, true);

SELECT pg_catalog.setval('"T_ALERT_ACKNOWLEDGE_ACK_ACK_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_ALERT_ALE_ALE_ID_seq"', 2, true);

SELECT pg_catalog.setval('"T_ALERT_CRITERIA_ACR_ACR_ID_seq"', 6, true);

SELECT pg_catalog.setval('"T_ALERT_SEQUENCE_ASE_ASE_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_ALERT_TRACKING_ATR_ATR_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_ALERT_TRACKING_EVENT_ATE_ATE_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_ALERT_VALUE_AVA_AVA_ID_seq"', 2, true);

SELECT pg_catalog.setval('"T_ASSET_AST_AST_ID_seq"', 1, true);

SELECT pg_catalog.setval('"T_ENGINE_ENG_ENG_ID_seq"', 1, true);

SELECT pg_catalog.setval('"T_INFORMATION_HISTORICAL_VALUE_IHV_IHV_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_INFORMATION_UNIT_TYPE_UTY_IUT_ID_seq"', 2, true);

SELECT pg_catalog.setval('"T_INFORMATION_UNIT_UNT_INU_ID_seq"', 6, true);

SELECT pg_catalog.setval('"T_INFORMATION_VALUE_IVA_IVA_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_MEDIA_MED_MED_ID_seq"', 2, true);

SELECT pg_catalog.setval('"T_MEDIA_VALUE_MEV_MEV_ID_seq"', 2, true);

SELECT pg_catalog.setval('"T_OPTION_OPT_OPT_ID_seq"', 1, true);

SELECT pg_catalog.setval('"T_ORGANIZATION_FIELD_OFI_OFI_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_ORGANIZATION_ORG_ORG_ID_seq"', 1, true);

SELECT pg_catalog.setval('"T_ORGANIZATION_TYPE_OTY_OTY_ID_seq"', 3, true);

SELECT pg_catalog.setval('"T_PACK_PCK_PCK_ID_seq"', 1, true);

SELECT pg_catalog.setval('"T_PLUGIN_PLG_PLG_ID_seq"', 1, true);

SELECT pg_catalog.setval('"T_PROBE_PRB_PRB_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_SEARCH_PARAMETER_SEP_SEP_ID_seq"', 1, true);

SELECT pg_catalog.setval('"T_SEARCH_TYPE_STY_STY_ID_seq"', 2, true);

SELECT pg_catalog.setval('"T_SOURCE_PARAMETER_SRP_SRP_ID_seq"', 1, true);

SELECT pg_catalog.setval('"T_SPACE_SPA_SPA_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_SYSLOG_SLO_SLO_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_USER_ACTION_ACT_UAC_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_USER_FIELD_UFI_UFI_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_USER_HISTORICAL_ACTION_UHA_UHA_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_USER_PROFILE_UPR_UPR_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_USER_RIGHT_URI_URI_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_USER_ROLE_URO_URO_ID_seq"', 1, false);

SELECT pg_catalog.setval('"T_USER_USR_USR_ID_seq"', 4, true);

SELECT pg_catalog.setval('auth_identity_id_seq', 4, true);

SELECT pg_catalog.setval('auth_info_id_seq', 4, true);

SELECT pg_catalog.setval('auth_token_id_seq', 1, false);

--
-- DATA INSERTION
--

INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (1, 0, 'lt', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (2, 0, 'le', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (3, 0, 'eq', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (4, 0, 'ne', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (5, 0, 'ge', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (6, 0, 'gt', NULL);

INSERT INTO "T_INFORMATION_UNIT_TYPE_UTY" ("IUT_ID", version, "IUT_NAME", "IUT_DELETE") VALUES (1, 0, 'text', NULL);
INSERT INTO "T_INFORMATION_UNIT_TYPE_UTY" ("IUT_ID", version, "IUT_NAME", "IUT_DELETE") VALUES (2, 0, 'number', NULL);

INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (3, 1);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (4, 1);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (1, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (2, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (3, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (4, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (5, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (6, 2);

INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (1, 0, 'log', NULL);
INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (2, 0, 'file', NULL);

INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (1, 0, 'text', 'path', NULL);

INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (1, 2);

INSERT INTO "T_PACK_PCK" ("PCK_ID", version, "PCK_NAME", "PCK_DELETE") VALUES (1, 0, 'alpha', NULL);

INSERT INTO "T_ORGANIZATION_TYPE_OTY"("OTY_ID", version, "OTY_NAME", "OTY_DELETE") VALUES (1, 0, 'Particulier', NULL);
INSERT INTO "T_ORGANIZATION_TYPE_OTY"("OTY_ID", version, "OTY_NAME", "OTY_DELETE") VALUES (2, 0, 'Association', NULL);
INSERT INTO "T_ORGANIZATION_TYPE_OTY"("OTY_ID", version, "OTY_NAME", "OTY_DELETE") VALUES (3, 0, 'Entreprise Française', NULL);

INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (1, 0, '12 avenue des Prés', 'Montigny le Bretonneux', '78180', 'ECHOES Technologies', NULL, 1, 3);

INSERT INTO "T_PROBE_PRB" ("PRB_ID", version, "PRB_CERT", "PRB_NAME", "PRB_DELETE", "PRB_ORG_ORG_ID") VALUES (6585, 0, 'temp', 'rhi-laptop-ea-probe', NULL, 1);

INSERT INTO "T_ASSET_AST" ("AST_ID", version, "AST_NAME", "AST_DELETE", "AST_IS_HOST", "AST_PRB_PRB_ID") VALUES (1, 0, 'rhi-laptop', NULL, true, 6585);

INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (1, 0, 'Linux - System', 'System', NULL);

INSERT INTO "TJ_AST_PLG" ("T_ASSET_AST_AST_ID", "T_PLUGIN_PLG_PLG_ID") VALUES (1, 1);

INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (1, 0, 'Kilo Bytes', 'Kb', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (2, 0, 'Packets', 'Pkts', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (3, 0, 'Bytes', 'Bytes', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (4, 0, 'name', 'name', NULL, 1);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (5, 0, 'load', 'load', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (6, 0, 'Time in USER_Hz', 'time in USER_Hz', NULL, 2);

INSERT INTO "T_SEARCH_TYPE_STY" ("STY_ID", version, "STY_NAME", "STY_DELETE") VALUES (1, 0, 'regex', NULL);
INSERT INTO "T_SEARCH_TYPE_STY" ("STY_ID", version, "STY_NAME", "STY_DELETE") VALUES (2, 0, 'location', NULL);

INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 1, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 2, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 3, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 4, 1, 2);

INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 1, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 9, 1, 1, 2, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 3, 0, 1, 3, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 5, 1, 1, 4, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 2, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 4, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 3, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 5, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 6, 1, 1, 1);

INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'CPU name', NULL, 1, 4, 1, 1, 4);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory free', NULL, 2, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Network interface name', NULL, 1, 2, 1, 1, 4);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Total Memory', NULL, 1, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Buffers', NULL, 3, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory cached', NULL, 4, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory Swap size', NULL, 5, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory Swap free', NULL, 6, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Receive bytes', NULL, 1, 2, 1, 2, 3);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Receive packets', NULL, 1, 2, 1, 3, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Receive errors', NULL, 1, 2, 1, 4, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Receive drops', NULL, 1, 2, 1, 5, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Transmit bytes', NULL, 1, 2, 1, 6, 3);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Transmit packets', NULL, 1, 2, 1, 7, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Transmit errors', NULL, 1, 2, 1, 8, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Transmit drop', NULL, 1, 2, 1, 9, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Load average on 1 minute', NULL, 1, 3, 1, 1, 5);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Load average on 5 minutes', NULL, 1, 3, 1, 2, 5);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Load average on 15 minutes', NULL, 1, 3, 1, 3, 5);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'user mode CPU usage', NULL, 1, 4, 1, 2, 6);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'user mode with low priority CPU usage', NULL, 1, 4, 1, 3, 6);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'system mode CPU usage', NULL, 1, 4, 1, 4, 6);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'inactive mode CPU usage', NULL, 1, 4, 1, 5, 6);

INSERT INTO "T_ALERT_VALUE_AVA" ("AVA_ID", version, "AVA_KEY_VALUE", "AVA_VALUE", "AVA_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "AVA_ACR_ACR_ID") VALUES (1, 0, NULL, '4762924', NULL, 2, 1, 1, 1, 1);
INSERT INTO "T_ALERT_VALUE_AVA" ("AVA_ID", version, "AVA_KEY_VALUE", "AVA_VALUE", "AVA_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "AVA_ACR_ACR_ID") VALUES (2, 0, NULL, '0.5', NULL, 1, 3, 1, 1, 5);

INSERT INTO "T_ENGINE_ENG" ("ENG_ID", version, "ENG_FQDN", "ENG_STATE", "ENG_DELETE", "ENG_KEEP_ALIVE", "ENG_NB_THREAD") VALUES (1, 0, 'Engine01', '0', NULL, NULL, 100);

INSERT INTO "T_ALERT_ALE" ("ALE_ID", version, "ALE_NAME", "ALE_CREA_DATE", "ALE_DELETE", "ALE_LAST_ATTEMPT", "ALE_THREAD_SLEEP", "ALE_AVA_AVA_ID", "ASE_FIRST_ID_ASE_ID", "ALE_ENG_ENG_ID") VALUES (1, 0, 'Occupation mémoire', '2012-09-08 23:48:24', NULL, '2012-09-11 17:16:23.836697', 0, 1, NULL, 1);
INSERT INTO "T_ALERT_ALE" ("ALE_ID", version, "ALE_NAME", "ALE_CREA_DATE", "ALE_DELETE", "ALE_LAST_ATTEMPT", "ALE_THREAD_SLEEP", "ALE_AVA_AVA_ID", "ASE_FIRST_ID_ASE_ID", "ALE_ENG_ENG_ID") VALUES (2, 0, 'Surcharge système', '2012-09-12 18:40:20', NULL, '2012-09-11 17:16:23.834179', 0, 2, NULL, 1);

INSERT INTO "T_MEDIA_MED" ("MED_ID", version, "MED_NAME", "MED_DELETE") VALUES (1, 0, 'mail', NULL);
INSERT INTO "T_MEDIA_MED" ("MED_ID", version, "MED_NAME", "MED_DELETE") VALUES (2, 0, 'sms', NULL);

INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (1, 0, 'ECHOES', 'Technologies', 'contact@echoes-tech.com', '', NULL, NULL, 1, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (2, 0, 'Romain', 'Hinfray', 'romain.hinfray@echoes-tech.com', '', NULL, NULL, 1, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (3, 0, 'Florent', 'Poinsaut', 'florent.poinsaut@echoes-tech.com', '', NULL, NULL, 1, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (4, 0, 'Thomas', 'Saquet', 'thomas.saquet@echoes-tech.com', '', NULL, NULL, 1, NULL);

INSERT INTO "T_MEDIA_VALUE_MEV" ("MEV_ID", version, "MEV_VALUE", "MEV_DELETE", "MEV_LAST_SEND", "MEV_NOTIF_END_OF_ALERT", "MEV_SNOOZE", "MEV_MED_MED_ID", "MEV_USR_USR_ID") VALUES (1, 0, 'neorom@gmail.com', NULL, '2012-09-11 17:18:51.243814', false, 60, 1, 2);
INSERT INTO "T_MEDIA_VALUE_MEV" ("MEV_ID", version, "MEV_VALUE", "MEV_DELETE", "MEV_LAST_SEND", "MEV_NOTIF_END_OF_ALERT", "MEV_SNOOZE", "MEV_MED_MED_ID", "MEV_USR_USR_ID") VALUES (2, 0, '+33607874128', NULL, '2012-09-11 17:19:14.894232', false, 10, 2, 2);

INSERT INTO "TJ_MEV_ALE" ("T_MEDIA_VALUE_MEV_MEV_ID", "T_ALERT_ALE_ALE_ID") VALUES (2, 1);
INSERT INTO "TJ_MEV_ALE" ("T_MEDIA_VALUE_MEV_MEV_ID", "T_ALERT_ALE_ALE_ID") VALUES (1, 2);
INSERT INTO "TJ_MEV_ALE" ("T_MEDIA_VALUE_MEV_MEV_ID", "T_ALERT_ALE_ALE_ID") VALUES (2, 2);

INSERT INTO "T_SEARCH_PARAMETER_SEP" ("SEP_ID", version, "SEP_FORMAT", "SEP_NAME", "SEP_DELETE") VALUES (1, 0, 'text', 'regex', NULL);

INSERT INTO "TJ_STY_SEP" ("T_SEARCH_TYPE_STY_STY_ID", "T_SEARCH_PARAMETER_SEP_SEP_ID") VALUES (1, 1);

INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (1, 1);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (1, 2);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (1, 3);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (1, 4);

INSERT INTO "T_OPTION_OPT" ("OPT_ID", version, "OPT_NAME", "OPT_DELETE") VALUES (1, 0, 'quotaasset', NULL);
INSERT INTO "T_OPTION_OPT" ("OPT_ID", version, "OPT_NAME", "OPT_DELETE") VALUES (2, 0, 'quotasms', NULL);

INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '5', NULL, 1, 1);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '10', NULL, 2, 1);

INSERT INTO "T_PACK_OPTION_POP" (version, "POP_VALUE", "POP_DELETE", "PCK_ID_PCK_ID", "OPT_ID_OPT_ID") VALUES (0, '5', NULL, 1, 1);
INSERT INTO "T_PACK_OPTION_POP" (version, "POP_VALUE", "POP_DELETE", "PCK_ID_PCK_ID", "OPT_ID_OPT_ID") VALUES (0, '10', NULL, 1, 2);

INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^MemTotal:\\s+([0-9]+)\\skB', NULL, 1, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^\\s*(\\w+):\\s*([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+', NULL, 1, 2, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^([0-9]+\\.[0-9]+)\\s([0-9]+\\.[0-9]+)\\s([0-9]+\\.[0-9]+)', NULL, 1, 3, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^(cpu[0-9]*)\\s+([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+', NULL, 1, 4, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^MemFree:\\s+([0-9]+)\\skB', NULL, 2, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^Buffers:\\s+([0-9]+)\\skB', NULL, 3, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^Cached:\\s+([0-9]+)\\skB', NULL, 4, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^SwapTotal:\\s+([0-9]+)\\skB', NULL, 5, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^SwapFree:\\s+([0-9]+)\\skB', NULL, 6, 1, 1, 1);

INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/meminfo', NULL, 1, 1, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/net/dev', NULL, 1, 2, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/loadavg', NULL, 1, 3, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/stat', NULL, 1, 4, 1);

INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_role) VALUES (1, 0, 1, '$2y$07$KUqtX0PFKFTrcEntY0rDU.2we1eSD79I0irzAh4wl2jFfvToSx4de', 'bcrypt', '1k/gdG0umxjokkEX', 1, 0, '2012-09-11 16:52:53.097319', 'contact@echoes-tech.com', '', '', 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_role) VALUES (2, 0, 2, '$2y$07$KUqtX0PFKFTrcEntY0rDU.2we1eSD79I0irzAh4wl2jFfvToSx4de', 'bcrypt', '1k/gdG0umxjokkEX', 1, 0, '2012-09-11 16:52:53.097319', 'romain.hinfray@echoes-tech.com', '', '', 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_role) VALUES (3, 0, 3, '$2y$07$KUqtX0PFKFTrcEntY0rDU.2we1eSD79I0irzAh4wl2jFfvToSx4de', 'bcrypt', '1k/gdG0umxjokkEX', 1, 0, '2012-09-11 16:52:53.097319', 'florent.poinsaut@echoes-tech.com', '', '', 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_role) VALUES (4, 0, 4, '$2y$07$KUqtX0PFKFTrcEntY0rDU.2we1eSD79I0irzAh4wl2jFfvToSx4de', 'bcrypt', '1k/gdG0umxjokkEX', 1, 0, '2012-09-11 16:52:53.097319', 'thomas.saquet@echoes-tech.com', '', '', 1);

INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (1, 0, 1, 'loginname', 'contact@echoes-tech.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (2, 0, 2, 'loginname', 'romain.hinfray@echoes-tech.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (3, 0, 3, 'loginname', 'florent.poinsaut@echoes-tech.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (4, 0, 4, 'loginname', 'thomas.saquet@echoes-tech.com');


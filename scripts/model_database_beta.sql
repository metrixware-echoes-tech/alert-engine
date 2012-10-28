--
-- PostgreSQL database dump
--

-- Dumped from database version 8.4.13
-- Dumped by pg_dump version 9.1.6
-- Started on 2012-10-28 19:39:45 CET

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

SET search_path = public, pg_catalog;

--
-- TOC entry 2450 (class 0 OID 0)
-- Dependencies: 142
-- Name: T_ADDON_ADO_ADO_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ADDON_ADO_ADO_ID_seq"', 4, true);


--
-- TOC entry 2451 (class 0 OID 0)
-- Dependencies: 197
-- Name: T_ALERT_ACKNOWLEDGE_ACK_ACK_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_ACKNOWLEDGE_ACK_ACK_ID_seq"', 1, false);


--
-- TOC entry 2452 (class 0 OID 0)
-- Dependencies: 184
-- Name: T_ALERT_ALE_ALE_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_ALE_ALE_ID_seq"', 19, true);


--
-- TOC entry 2453 (class 0 OID 0)
-- Dependencies: 153
-- Name: T_ALERT_CRITERIA_ACR_ACR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_CRITERIA_ACR_ACR_ID_seq"', 6, true);


--
-- TOC entry 2454 (class 0 OID 0)
-- Dependencies: 219
-- Name: T_ALERT_MEDIA_SPECIALIZATION_AMS_AMS_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_MEDIA_SPECIALIZATION_AMS_AMS_ID_seq"', 28, true);


--
-- TOC entry 2455 (class 0 OID 0)
-- Dependencies: 180
-- Name: T_ALERT_SEQUENCE_ASE_ASE_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_SEQUENCE_ASE_ASE_ID_seq"', 1, false);


--
-- TOC entry 2456 (class 0 OID 0)
-- Dependencies: 186
-- Name: T_ALERT_TRACKING_ATR_ATR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_TRACKING_ATR_ATR_ID_seq"', 6451, true);


--
-- TOC entry 2457 (class 0 OID 0)
-- Dependencies: 213
-- Name: T_ALERT_TRACKING_EVENT_ATE_ATE_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_TRACKING_EVENT_ATE_ATE_ID_seq"', 103, true);


--
-- TOC entry 2458 (class 0 OID 0)
-- Dependencies: 155
-- Name: T_ALERT_VALUE_AVA_AVA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_VALUE_AVA_AVA_ID_seq"', 19, true);


--
-- TOC entry 2459 (class 0 OID 0)
-- Dependencies: 199
-- Name: T_ASSET_AST_AST_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ASSET_AST_AST_ID_seq"', 18, true);


--
-- TOC entry 2460 (class 0 OID 0)
-- Dependencies: 182
-- Name: T_ENGINE_ENG_ENG_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ENGINE_ENG_ENG_ID_seq"', 1, true);


--
-- TOC entry 2461 (class 0 OID 0)
-- Dependencies: 221
-- Name: T_INFORMATION_HISTORICAL_VALUE_IHV_IHV_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_HISTORICAL_VALUE_IHV_IHV_ID_seq"', 1, false);


--
-- TOC entry 2462 (class 0 OID 0)
-- Dependencies: 148
-- Name: T_INFORMATION_UNIT_TYPE_UTY_IUT_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_UNIT_TYPE_UTY_IUT_ID_seq"', 2, true);


--
-- TOC entry 2463 (class 0 OID 0)
-- Dependencies: 150
-- Name: T_INFORMATION_UNIT_UNT_INU_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_UNIT_UNT_INU_ID_seq"', 7, true);


--
-- TOC entry 2464 (class 0 OID 0)
-- Dependencies: 203
-- Name: T_INFORMATION_VALUE_IVA_IVA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_VALUE_IVA_IVA_ID_seq"', 1, false);


--
-- TOC entry 2465 (class 0 OID 0)
-- Dependencies: 157
-- Name: T_MEDIA_MED_MED_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_MEDIA_MED_MED_ID_seq"', 2, true);


--
-- TOC entry 2466 (class 0 OID 0)
-- Dependencies: 171
-- Name: T_MEDIA_VALUE_MEV_MEV_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_MEDIA_VALUE_MEV_MEV_ID_seq"', 95, true);


--
-- TOC entry 2467 (class 0 OID 0)
-- Dependencies: 173
-- Name: T_OPTION_OPT_OPT_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_OPTION_OPT_OPT_ID_seq"', 1, true);


--
-- TOC entry 2468 (class 0 OID 0)
-- Dependencies: 210
-- Name: T_ORGANIZATION_FIELD_OFI_OFI_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ORGANIZATION_FIELD_OFI_OFI_ID_seq"', 1, false);


--
-- TOC entry 2469 (class 0 OID 0)
-- Dependencies: 165
-- Name: T_ORGANIZATION_ORG_ORG_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ORGANIZATION_ORG_ORG_ID_seq"', 37, true);


--
-- TOC entry 2470 (class 0 OID 0)
-- Dependencies: 163
-- Name: T_ORGANIZATION_TYPE_OTY_OTY_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ORGANIZATION_TYPE_OTY_OTY_ID_seq"', 3, true);


--
-- TOC entry 2471 (class 0 OID 0)
-- Dependencies: 161
-- Name: T_PACK_PCK_PCK_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_PACK_PCK_PCK_ID_seq"', 1, true);


--
-- TOC entry 2472 (class 0 OID 0)
-- Dependencies: 140
-- Name: T_PLUGIN_PLG_PLG_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_PLUGIN_PLG_PLG_ID_seq"', 2, true);


--
-- TOC entry 2473 (class 0 OID 0)
-- Dependencies: 188
-- Name: T_PROBE_PRB_PRB_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_PROBE_PRB_PRB_ID_seq"', 20, true);


--
-- TOC entry 2474 (class 0 OID 0)
-- Dependencies: 193
-- Name: T_SEARCH_PARAMETER_SEP_SEP_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SEARCH_PARAMETER_SEP_SEP_ID_seq"', 2, true);


--
-- TOC entry 2475 (class 0 OID 0)
-- Dependencies: 145
-- Name: T_SEARCH_TYPE_STY_STY_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SEARCH_TYPE_STY_STY_ID_seq"', 3, true);


--
-- TOC entry 2476 (class 0 OID 0)
-- Dependencies: 195
-- Name: T_SOURCE_PARAMETER_SRP_SRP_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SOURCE_PARAMETER_SRP_SRP_ID_seq"', 7, true);


--
-- TOC entry 2477 (class 0 OID 0)
-- Dependencies: 205
-- Name: T_SPACE_SPA_SPA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SPACE_SPA_SPA_ID_seq"', 1, false);


--
-- TOC entry 2478 (class 0 OID 0)
-- Dependencies: 190
-- Name: T_SYSLOG_HISTORY_SLH_SLH_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SYSLOG_HISTORY_SLH_SLH_ID_seq"', 1, false);


--
-- TOC entry 2479 (class 0 OID 0)
-- Dependencies: 201
-- Name: T_SYSLOG_SLO_SLO_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SYSLOG_SLO_SLO_ID_seq"', 1, false);


--
-- TOC entry 2480 (class 0 OID 0)
-- Dependencies: 177
-- Name: T_USER_ACTION_ACT_UAC_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_ACTION_ACT_UAC_ID_seq"', 1, false);


--
-- TOC entry 2481 (class 0 OID 0)
-- Dependencies: 223
-- Name: T_USER_FIELD_UFI_UFI_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_FIELD_UFI_UFI_ID_seq"', 1, false);


--
-- TOC entry 2482 (class 0 OID 0)
-- Dependencies: 217
-- Name: T_USER_HISTORICAL_ACTION_UHA_UHA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_HISTORICAL_ACTION_UHA_UHA_ID_seq"', 1, false);


--
-- TOC entry 2483 (class 0 OID 0)
-- Dependencies: 167
-- Name: T_USER_PROFILE_UPR_UPR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_PROFILE_UPR_UPR_ID_seq"', 1, false);


--
-- TOC entry 2484 (class 0 OID 0)
-- Dependencies: 207
-- Name: T_USER_RIGHT_URI_URI_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_RIGHT_URI_URI_ID_seq"', 1, false);


--
-- TOC entry 2485 (class 0 OID 0)
-- Dependencies: 159
-- Name: T_USER_ROLE_URO_URO_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_ROLE_URO_URO_ID_seq"', 1, false);


--
-- TOC entry 2486 (class 0 OID 0)
-- Dependencies: 169
-- Name: T_USER_USR_USR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_USR_USR_ID_seq"', 42, true);


--
-- TOC entry 2487 (class 0 OID 0)
-- Dependencies: 228
-- Name: auth_identity_id_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('auth_identity_id_seq', 42, true);


--
-- TOC entry 2488 (class 0 OID 0)
-- Dependencies: 226
-- Name: auth_info_id_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('auth_info_id_seq', 42, true);


--
-- TOC entry 2489 (class 0 OID 0)
-- Dependencies: 230
-- Name: auth_token_id_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('auth_token_id_seq', 909, true);


--
-- TOC entry 2394 (class 0 OID 48674)
-- Dependencies: 154 2446
-- Data for Name: T_ALERT_CRITERIA_ACR; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (1, 0, 'lt', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (2, 0, 'le', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (3, 0, 'eq', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (4, 0, 'ne', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (5, 0, 'ge', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (6, 0, 'gt', NULL);


--
-- TOC entry 2391 (class 0 OID 48629)
-- Dependencies: 149 2446
-- Data for Name: T_INFORMATION_UNIT_TYPE_UTY; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_UNIT_TYPE_UTY" ("IUT_ID", version, "IUT_NAME", "IUT_DELETE") VALUES (1, 0, 'text', NULL);
INSERT INTO "T_INFORMATION_UNIT_TYPE_UTY" ("IUT_ID", version, "IUT_NAME", "IUT_DELETE") VALUES (2, 0, 'number', NULL);


--
-- TOC entry 2440 (class 0 OID 49430)
-- Dependencies: 234 2391 2394 2446
-- Data for Name: TJ_ACR_IUT; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (3, 1);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (4, 1);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (1, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (2, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (3, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (4, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (5, 2);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (6, 2);


--
-- TOC entry 2387 (class 0 OID 48574)
-- Dependencies: 143 2446
-- Data for Name: T_ADDON_ADO; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (2, 0, 'file', NULL);
INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (3, 0, 'log', NULL);
INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (4, 0, 'mysql', NULL);
INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (1, 0, 'system(non exist)', NULL);


--
-- TOC entry 2417 (class 0 OID 49036)
-- Dependencies: 196 2446
-- Data for Name: T_SOURCE_PARAMETER_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (1, 0, 'text', 'path', NULL);
INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (2, 0, 'text', 'host', NULL);
INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (3, 0, 'text', 'user', NULL);
INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (4, 0, 'text', 'passwd', NULL);
INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (6, 0, 'text', 'db', NULL);
INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (7, 0, 'text', 'port', NULL);


--
-- TOC entry 2441 (class 0 OID 49447)
-- Dependencies: 235 2387 2417 2446
-- Data for Name: TJ_ADO_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (1, 2);
INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (2, 4);
INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (3, 4);
INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (4, 4);
INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (6, 4);
INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (7, 4);


--
-- TOC entry 2392 (class 0 OID 48640)
-- Dependencies: 151 2391 2446
-- Data for Name: T_INFORMATION_UNIT_UNT; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (1, 0, 'Kilo Bytes', 'Kb', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (2, 0, 'Packets', 'Pkts', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (3, 0, 'Bytes', 'Bytes', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (4, 0, 'name', 'name', NULL, 1);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (5, 0, 'load', 'load', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (6, 0, 'Time in USER_Hz', 'time in USER_Hz', NULL, 2);


--
-- TOC entry 2386 (class 0 OID 48563)
-- Dependencies: 141 2446
-- Data for Name: T_PLUGIN_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (1, 0, 'Linux - System', 'System', NULL);
INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (2, 0, 'Linux - Syslog', 'Syslog', NULL);
INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (3, 0, 'Traffic reseau mensuel site web tasoeur', 'Ispconfig-mysql-network', NULL);


--
-- TOC entry 2389 (class 0 OID 48600)
-- Dependencies: 146 2446
-- Data for Name: T_SEARCH_TYPE_STY; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_TYPE_STY" ("STY_ID", version, "STY_NAME", "STY_DELETE") VALUES (1, 0, 'regex', NULL);
INSERT INTO "T_SEARCH_TYPE_STY" ("STY_ID", version, "STY_NAME", "STY_DELETE") VALUES (2, 0, 'location', NULL);
INSERT INTO "T_SEARCH_TYPE_STY" ("STY_ID", version, "STY_NAME", "STY_DELETE") VALUES (3, 0, 'query', NULL);


--
-- TOC entry 2388 (class 0 OID 48583)
-- Dependencies: 144 2387 2386 2446
-- Data for Name: T_SOURCE_SRC; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 1, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 2, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 3, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 4, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 1, 3, 4);


--
-- TOC entry 2390 (class 0 OID 48609)
-- Dependencies: 147 2389 2388 2446
-- Data for Name: T_SEARCH_SEA; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 1, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 9, 1, 1, 2, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 3, 0, 1, 3, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 5, 1, 1, 4, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 2, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 4, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 3, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 5, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 6, 1, 1, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_POS_KEY_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (0, 'default', NULL, false, 1, 0, 1, 1, 3, 3);


--
-- TOC entry 2393 (class 0 OID 48654)
-- Dependencies: 152 2392 2390 2446
-- Data for Name: T_INFORMATION_INF; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Memory free', NULL, false, true, 2, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Load average on 1 minute', NULL, false, true, 1, 3, 1, 1, 5);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'CPU name', NULL, false, false, 1, 4, 1, 1, 4);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Network interface name', NULL, false, false, 1, 2, 1, 1, 4);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Total Memory', NULL, false, true, 1, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Buffers', NULL, false, true, 3, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Memory cached', NULL, false, true, 4, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Memory Swap size', NULL, false, true, 5, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Memory Swap free', NULL, false, true, 6, 1, 1, 1, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Receive bytes', NULL, true, false, 1, 2, 1, 2, 3);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Receive packets', NULL, true, true, 1, 2, 1, 3, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Receive errors', NULL, true, true, 1, 2, 1, 4, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Receive drops', NULL, true, true, 1, 2, 1, 5, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Transmit bytes', NULL, true, false, 1, 2, 1, 6, 3);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Transmit packets', NULL, true, true, 1, 2, 1, 7, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Transmit errors', NULL, true, true, 1, 2, 1, 8, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Transmit drop', NULL, true, true, 1, 2, 1, 9, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Load average on 5 minutes', NULL, false, true, 1, 3, 1, 2, 5);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Load average on 15 minutes', NULL, false, true, 1, 3, 1, 3, 5);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'user mode CPU usage', NULL, true, false, 1, 4, 1, 2, 6);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'user mode with low priority CPU usage', NULL, true, false, 1, 4, 1, 3, 6);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'system mode CPU usage', NULL, true, false, 1, 4, 1, 4, 6);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'inactive mode CPU usage', NULL, true, false, 1, 4, 1, 5, 6);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "INF_CALCULATE", "INF_DISPLAY", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INU_ID_INU_ID") VALUES (0, 'Trafic reseau mensuel site web client', NULL, false, false, 1, 1, 3, 1, 1);


--
-- TOC entry 2395 (class 0 OID 48685)
-- Dependencies: 156 2394 2393 2446
-- Data for Name: T_ALERT_VALUE_AVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2409 (class 0 OID 48902)
-- Dependencies: 181 2395 2446
-- Data for Name: T_ALERT_SEQUENCE_ASE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2410 (class 0 OID 48920)
-- Dependencies: 183 2446
-- Data for Name: T_ENGINE_ENG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ENGINE_ENG" ("ENG_ID", version, "ENG_FQDN", "ENG_STATE", "ENG_DELETE", "ENG_KEEP_ALIVE", "ENG_NB_THREAD") VALUES (1, 0, 'Engine01', '0', NULL, NULL, 100);


--
-- TOC entry 2411 (class 0 OID 48931)
-- Dependencies: 185 2410 2409 2395 2446
-- Data for Name: T_ALERT_ALE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2399 (class 0 OID 48739)
-- Dependencies: 164 2446
-- Data for Name: T_ORGANIZATION_TYPE_OTY; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ORGANIZATION_TYPE_OTY" ("OTY_ID", version, "OTY_NAME", "OTY_DELETE") VALUES (1, 0, 'Particulier', NULL);
INSERT INTO "T_ORGANIZATION_TYPE_OTY" ("OTY_ID", version, "OTY_NAME", "OTY_DELETE") VALUES (2, 0, 'Association', NULL);
INSERT INTO "T_ORGANIZATION_TYPE_OTY" ("OTY_ID", version, "OTY_NAME", "OTY_DELETE") VALUES (3, 0, 'Entreprise Française', NULL);


--
-- TOC entry 2398 (class 0 OID 48728)
-- Dependencies: 162 2446
-- Data for Name: T_PACK_PCK; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PACK_PCK" ("PCK_ID", version, "PCK_NAME", "PCK_DELETE") VALUES (1, 0, 'alpha', NULL);


--
-- TOC entry 2400 (class 0 OID 48750)
-- Dependencies: 166 2399 2398 2446
-- Data for Name: T_ORGANIZATION_ORG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (3, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (4, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (5, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (6, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (7, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (8, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (9, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (10, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (14, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (15, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (16, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (17, 0, '6 bis rue Albert Meunier', 'Aÿ', '51160', 'GayuxWeb', NULL, 1, 2);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (18, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (19, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (36, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (22, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (23, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (24, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (25, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (26, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (27, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (28, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (29, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (30, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (31, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (32, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (37, 0, '', '', '', '', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (34, 0, '', '', '', '', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (35, 0, '', '', '', '', NULL, NULL, NULL);


--
-- TOC entry 2413 (class 0 OID 48978)
-- Dependencies: 189 2400 2446
-- Data for Name: T_PROBE_PRB; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2419 (class 0 OID 49068)
-- Dependencies: 200 2413 2446
-- Data for Name: T_ASSET_AST; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2444 (class 0 OID 49498)
-- Dependencies: 238 2419 2411 2446
-- Data for Name: TJ_AST_ALE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2445 (class 0 OID 49515)
-- Dependencies: 239 2386 2419 2446
-- Data for Name: TJ_AST_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2425 (class 0 OID 49173)
-- Dependencies: 211 2446
-- Data for Name: T_ORGANIZATION_FIELD_OFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2442 (class 0 OID 49464)
-- Dependencies: 236 2425 2399 2446
-- Data for Name: TJ_OFI_OTY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2416 (class 0 OID 49025)
-- Dependencies: 194 2446
-- Data for Name: T_SEARCH_PARAMETER_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_PARAMETER_SEP" ("SEP_ID", version, "SEP_FORMAT", "SEP_NAME", "SEP_DELETE") VALUES (1, 0, 'text', 'regex', NULL);
INSERT INTO "T_SEARCH_PARAMETER_SEP" ("SEP_ID", version, "SEP_FORMAT", "SEP_NAME", "SEP_DELETE") VALUES (2, 0, 'text', 'query', NULL);


--
-- TOC entry 2438 (class 0 OID 49396)
-- Dependencies: 232 2416 2389 2446
-- Data for Name: TJ_STY_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_STY_SEP" ("T_SEARCH_TYPE_STY_STY_ID", "T_SEARCH_PARAMETER_SEP_SEP_ID") VALUES (1, 1);
INSERT INTO "TJ_STY_SEP" ("T_SEARCH_TYPE_STY_STY_ID", "T_SEARCH_PARAMETER_SEP_SEP_ID") VALUES (3, 2);


--
-- TOC entry 2401 (class 0 OID 48771)
-- Dependencies: 168 2446
-- Data for Name: T_USER_PROFILE_UPR; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2397 (class 0 OID 48717)
-- Dependencies: 160 2446
-- Data for Name: T_USER_ROLE_URO; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2402 (class 0 OID 48782)
-- Dependencies: 170 2401 2400 2397 2446
-- Data for Name: T_USER_USR; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (42, 0, 'Rémi', 'Noel', 'remi@reminoel.net', '', NULL, NULL, 37, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (7, 0, 'Louis', 'Duruflé', 'louis@durufle.eu', '', NULL, NULL, 4, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (8, 0, 'Sylvain', 'HERLÉDAN', 'sylvain.herledan_echoes@shadowz.sytes.net', '', NULL, NULL, 5, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (9, 0, 'Valérian', 'Rossigneux', 'cyberval@gmail.com', '', NULL, NULL, 6, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (10, 0, 'Alfred', 'Sawaya', 'alfred@huji.fr', '', NULL, NULL, 7, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (11, 0, 'JF', 'SAQUET', 'jffsaquet@gmail.com', '', NULL, NULL, 8, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (12, 0, 'Emilien', 'Bertin', 'bertin.emilien@gmail.com', '', NULL, NULL, 9, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (13, 0, 'Baptiste', 'Jacquemet', 'baptiste.jacquemet@gmail.com', '', NULL, NULL, 10, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (17, 0, 'benjamin', 'maze', 'benjamin.maze@gmail.com', '', NULL, NULL, 14, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (18, 0, 'julien', 'jordan', 'julien.jordan@gmail.com', '', NULL, NULL, 15, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (38, 4, 'Romain', 'Hinfray', 'romain.hinfray@echoes-tech.com', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (6, 0, 'mathieu', 'chateau', 'chateaum+echoes@gmail.com', '', NULL, NULL, 3, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (19, 0, 'Thomas', 'MARTELET', 'thomas.martelet@gmail.com', '', NULL, NULL, 16, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (20, 0, 'Paul', 'Fariello', 'paul+echoes@fariello.eu', '', NULL, NULL, 18, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (39, 0, 'Morgan', 'Lamant', 'morgan.lamant@gmail.com', '', NULL, NULL, 34, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (40, 0, 'Audrey', 'Duwicquet', 'phenixnoir@gmail.com', '', NULL, NULL, 35, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (41, 0, 'Xavier', 'Mehrenberger', 'xavier.mehrenberger@gmail.com', '', NULL, NULL, 36, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (21, 0, 'Pierre', 'Boutet', 'pyro853@gmail.com', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (27, 0, 'Philippe', 'Poinsaut', 'poinsaut.philippe@wanadoo.fr', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (28, 0, 'Guy', 'Hinfray', 'hinfray.guy@neuf.fr', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (29, 0, 'Sebastien', 'Viger', 'sebastienviger@gmail.com', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (30, 0, 'François', 'Devaux', 'francois.devaux@gmail.com', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (31, 0, 'Jean-François', 'Saquet', 'jffsaquet@free.fr', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (32, 0, 'Bernard', 'Mahe', 'bernard.mahe@thedstock.com', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (33, 0, 'Amaury', 'Leroy', 'fettprodj@hotmail.com', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (34, 0, 'Sébastien', 'Rummelhardt', 's3b.rum@gmail.com', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (35, 0, 'Thomas', 'Hahusseau', 'thomas.hahusseau@gmail.com', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (3, 2, 'Florent', 'Poinsaut', 'florent.poinsaut@echoes-tech.com', '', NULL, NULL, 17, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (4, 8, 'Thomas', 'Saquet', 'thomas.saquet@echoes-tech.com', '', NULL, NULL, 17, NULL);


--
-- TOC entry 2439 (class 0 OID 49413)
-- Dependencies: 233 2402 2400 2446
-- Data for Name: TJ_USR_ORG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (37, 42);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (3, 6);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (4, 7);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (5, 8);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (6, 9);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (7, 10);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (8, 11);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (9, 12);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (10, 13);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (14, 17);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (15, 18);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (16, 19);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (18, 20);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 33);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 32);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 31);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 30);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 29);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 28);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 27);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 21);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 34);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 35);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (17, 38);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (34, 39);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (35, 40);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (36, 41);


--
-- TOC entry 2433 (class 0 OID 49324)
-- Dependencies: 224 2446
-- Data for Name: T_USER_FIELD_UFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2443 (class 0 OID 49481)
-- Dependencies: 237 2433 2402 2446
-- Data for Name: TJ_USR_UFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2422 (class 0 OID 49131)
-- Dependencies: 206 2446
-- Data for Name: T_SPACE_SPA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2423 (class 0 OID 49142)
-- Dependencies: 208 2446
-- Data for Name: T_USER_RIGHT_URI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2424 (class 0 OID 49151)
-- Dependencies: 209 2423 2401 2422 2446
-- Data for Name: T_ACCESS_CONTROL_LIST_ACL; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2418 (class 0 OID 49047)
-- Dependencies: 198 2402 2411 2446
-- Data for Name: T_ALERT_ACKNOWLEDGE_ACK; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2396 (class 0 OID 48706)
-- Dependencies: 158 2446
-- Data for Name: T_MEDIA_MED; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_MEDIA_MED" ("MED_ID", version, "MED_NAME", "MED_DELETE") VALUES (1, 0, 'mail', NULL);
INSERT INTO "T_MEDIA_MED" ("MED_ID", version, "MED_NAME", "MED_DELETE") VALUES (2, 0, 'sms', NULL);


--
-- TOC entry 2403 (class 0 OID 48808)
-- Dependencies: 172 2402 2396 2446
-- Data for Name: T_MEDIA_VALUE_MEV; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2431 (class 0 OID 49275)
-- Dependencies: 220 2403 2411 2446
-- Data for Name: T_ALERT_MEDIA_SPECIALIZATION_AMS; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2412 (class 0 OID 48957)
-- Dependencies: 187 2411 2403 2446
-- Data for Name: T_ALERT_TRACKING_ATR; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2427 (class 0 OID 49202)
-- Dependencies: 214 2412 2446
-- Data for Name: T_ALERT_TRACKING_EVENT_ATE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2414 (class 0 OID 48994)
-- Dependencies: 191 2413 2446
-- Data for Name: T_SYSLOG_HISTORY_SLH; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2420 (class 0 OID 49084)
-- Dependencies: 202 2413 2446
-- Data for Name: T_SYSLOG_SLO; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2432 (class 0 OID 49293)
-- Dependencies: 222 2393 2414 2420 2419 2446
-- Data for Name: T_INFORMATION_HISTORICAL_VALUE_IHV; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2421 (class 0 OID 49100)
-- Dependencies: 204 2393 2414 2420 2419 2446
-- Data for Name: T_INFORMATION_VALUE_IVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2404 (class 0 OID 48829)
-- Dependencies: 174 2446
-- Data for Name: T_OPTION_OPT; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_OPTION_OPT" ("OPT_ID", version, "OPT_NAME", "OPT_DELETE") VALUES (1, 0, 'quotaasset', NULL);
INSERT INTO "T_OPTION_OPT" ("OPT_ID", version, "OPT_NAME", "OPT_DELETE") VALUES (2, 0, 'quotasms', NULL);


--
-- TOC entry 2408 (class 0 OID 48882)
-- Dependencies: 179 2400 2404 2446
-- Data for Name: T_OPTION_VALUE_OPV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 2, 36);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 2, 37);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 2, 9);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 1, 4);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 1, 6);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 1, 7);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 2, 4);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 2, 6);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 2, 7);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '1', NULL, 1, 3);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (1, '0', NULL, 2, 3);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 2, 8);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 1, 8);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '0', NULL, 2, 14);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (2, '0', NULL, 2, 16);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (0, '4', NULL, 1, 17);
INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (1, '0', NULL, 2, 17);


--
-- TOC entry 2426 (class 0 OID 49182)
-- Dependencies: 212 2400 2425 2446
-- Data for Name: T_ORGANIZATION_VALUE_OVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2405 (class 0 OID 48838)
-- Dependencies: 175 2404 2398 2446
-- Data for Name: T_PACK_OPTION_POP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PACK_OPTION_POP" (version, "POP_VALUE", "POP_DELETE", "PCK_ID_PCK_ID", "OPT_ID_OPT_ID") VALUES (0, '5', NULL, 1, 1);
INSERT INTO "T_PACK_OPTION_POP" (version, "POP_VALUE", "POP_DELETE", "PCK_ID_PCK_ID", "OPT_ID_OPT_ID") VALUES (0, '10', NULL, 1, 2);


--
-- TOC entry 2428 (class 0 OID 49216)
-- Dependencies: 215 2416 2390 2446
-- Data for Name: T_SEARCH_PARAMETER_VALUE_SEV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^MemTotal:\\s+([0-9]+)\\skB', NULL, 1, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^\\s*(\\w+):\\s*([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+', NULL, 1, 2, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^([0-9]+\\.[0-9]+)\\s([0-9]+\\.[0-9]+)\\s([0-9]+\\.[0-9]+)', NULL, 1, 3, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^(cpu[0-9]*)\\s+([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+', NULL, 1, 4, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^MemFree:\\s+([0-9]+)\\skB', NULL, 2, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^Buffers:\\s+([0-9]+)\\skB', NULL, 3, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^Cached:\\s+([0-9]+)\\skB', NULL, 4, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^SwapTotal:\\s+([0-9]+)\\skB', NULL, 5, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^SwapFree:\\s+([0-9]+)\\skB', NULL, 6, 1, 1, 1);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, 'SELECT sum( traffic_bytes ) AS t FROM web_traffic WHERE hostname = ''tasoeur.biz'' AND YEAR( traffic_date ) = ''2012'' AND MONTH( traffic_date ) = ''10''', NULL, 1, 1, 3, 2);


--
-- TOC entry 2406 (class 0 OID 48856)
-- Dependencies: 176 2392 2390 2446
-- Data for Name: T_SEARCH_UNIT_SEU; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 1, 1, 1, 1);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 1, 3, 1, 1);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 2, 1, 1, 4);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 2, 1, 2, 3);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 2, 1, 3, 2);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 2, 1, 4, 2);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 2, 1, 5, 2);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 2, 1, 6, 3);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 2, 1, 7, 2);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 2, 1, 8, 2);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 2, 1, 9, 2);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 3, 1, 1, 5);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 3, 1, 2, 5);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 3, 1, 3, 5);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 4, 1, 1, 4);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 4, 1, 2, 6);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 4, 1, 3, 6);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 4, 1, 4, 6);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 1, 4, 1, 5, 6);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 2, 1, 1, 1, 1);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 3, 1, 1, 1, 1);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 4, 1, 1, 1, 1);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 5, 1, 1, 1, 1);
INSERT INTO "T_SEARCH_UNIT_SEU" (version, "SEU_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "SEU_INU_INU_ID") VALUES (0, NULL, 6, 1, 1, 1, 1);


--
-- TOC entry 2429 (class 0 OID 49234)
-- Dependencies: 216 2388 2417 2446
-- Data for Name: T_SOURCE_PARAMETER_VALUE_SPV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/meminfo', NULL, 1, 1, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/net/dev', NULL, 1, 2, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/loadavg', NULL, 1, 3, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/stat', NULL, 1, 4, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, 'gayux.fr', NULL, 2, 1, 3);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, 'root', NULL, 3, 1, 3);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, 'PG0VkJ5yLZoi0<u', NULL, 4, 1, 3);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, 'gayuxweb', NULL, 6, 1, 3);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '0', NULL, 7, 1, 3);


--
-- TOC entry 2407 (class 0 OID 48873)
-- Dependencies: 178 2446
-- Data for Name: T_USER_ACTION_ACT; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2415 (class 0 OID 49008)
-- Dependencies: 192 2402 2402 2446
-- Data for Name: T_USER_HIERARCHY_UHI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2430 (class 0 OID 49254)
-- Dependencies: 218 2407 2402 2446
-- Data for Name: T_USER_HISTORICAL_ACTION_UHA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2434 (class 0 OID 49333)
-- Dependencies: 225 2433 2402 2446
-- Data for Name: T_USER_VALUE_UVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2435 (class 0 OID 49353)
-- Dependencies: 227 2402 2446
-- Data for Name: auth_info; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (21, 12, 21, '$2y$07$Q0PhUVn0XTP4bCfKLyLtX.VTQ7BMJ5pm/N/N.Mdoy1gwnu64bR5ca', 'bcrypt', 'KdcYzveTztHL7Cod', 1, 0, '2012-10-07 14:10:32.289605', 'pyro853@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (40, 9, 40, '$2y$07$P1P3ZDnrSUHhUjnVXUu1R.sAb7rVw99pqLaBQ.Xg.9CPyDsal7EMa', 'bcrypt', 'GtylZmQbcZZWel7L', 1, 0, '2012-10-08 16:06:04.242555', 'phenixnoir@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (39, 1, 39, '$2y$07$QU6tLA7tWlWvOxOtalP1OO7TKgQFwdQ8/DJhdHn9.0z97zLsQ2jti', 'bcrypt', 'Io/4/obv1C4/rtwA', 1, 0, NULL, 'morgan.lamant@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (17, 10, 17, '$2y$07$TETGT1HXbVTGSjTLazjvTu0osVnDPH8GGN6gydDV0jDPFedcfEbai', 'bcrypt', 'TeHWrYuuHRUMsYqW', 1, 0, '2012-10-08 07:09:20.673437', 'benjamin.maze@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (42, 1, 42, '$2y$07$ZVewWlLoKCqzPlfTUBfURevsjN75YvJ0wA1wdPJt7yc6bCFQU.XJC', 'bcrypt', 'mx2bsj0K5FxUX8VN', 1, 0, NULL, 'remi@reminoel.net', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (19, 45, 19, '$2y$07$XjjvKk3SWi3uRRHObCmzZu8qnRwf5sxxeCYyiZ0OqMdalvQX5OUnq', 'bcrypt', 'fYq2nTbNpM2PtJ5o', 1, 3, '2012-10-26 10:04:20.527913', 'thomas.martelet@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (38, 54, 38, '$2y$07$YjLNO0HfRUTmUUeuRRD2Yeowh1KZ5i8G92Nj9niSpcu.Np1RqdF/K', 'bcrypt', 'jSOCbaMehYh0M1xj', 1, 0, '2012-10-26 10:04:55.136964', '', 'romain.hinfray@echoes-tech.com', '57Dlwwp6VUsfyghmrViXFw==', '2012-10-08 18:21:48.748095', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (33, 5, 33, '$2y$07$TFX4RFfoYzXnRRjOb0S3cOsS1jeF2pdAf2BBEtF49a/rYjADI178i', 'bcrypt', 'TvzLxjkViM9Pwe9y', 1, 5, '2012-10-08 21:03:04.408776', '', 'fettprodj@hotmail.com', '/F5ELcmQJZv/f9DLWBcSIw==', '2012-10-08 17:43:09.104434', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (18, 14, 18, '$2y$07$aybVPULpPEzwLyPKRS6yQugDyqHAncp7ImmX23/P9pqWHISk/mS0q', 'bcrypt', 'sGWEckDmr7DLMO4K', 1, 0, '2012-09-20 07:44:05.764405', 'julien.jordan@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (27, 0, 27, '$2y$07$ZhbCPljPL1/pKS7vYljEa.GpoNqkH8affw7dJQwJMyRgSADddXlui', 'bcrypt', 'n7DFyQ7pk1OqjyFp', 1, 0, NULL, '', 'poinsaut.philippe@wanadoo.fr', 'hzJz8JoEjDmSBVPyMpsVew==', '2012-10-08 17:27:58.974845', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (41, 2, 41, '$2y$07$cjLRSlfrOkS2Kya3blTGM.t.Y8A6eWv6F4IjdF2Lyud6UeXkWfJvy', 'bcrypt', 'zSSRxmBe83G9vuH8', 1, 0, '2012-10-08 21:10:30.611992', 'xavier.mehrenberger@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (28, 0, 28, '$2y$07$cDnoRy3raSz2MCK0WUftOeIaf2QdXyxj1Ix2j1l91MJ6N4vjKU8re', 'bcrypt', 'xZjONmqMx8C6ahoB', 1, 0, NULL, '', 'hinfray.guy@neuf.fr', '4rjzs88GtGQQdqeor/Z/Lg==', '2012-10-08 17:37:14.402524', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (29, 0, 29, '$2y$07$KkHHXyXPTS7SbA3CbxfjLO73m/ON25SXZngOXVYsA1thdSfqJ9uLK', 'bcrypt', '2bIgFQUOTt.Dw8e5', 1, 0, NULL, '', 'sebastienviger@gmail.com', 'NBfJrUnY6ydzjeZHwAJ5OA==', '2012-10-08 17:38:36.223214', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (30, 0, 30, '$2y$07$WjH4bkrrZSysYBLRTC3oM..U0ORikwEwksjOvM4sI7YeNK2Syrps.', 'bcrypt', 'bRzvkmmM.h3STNj8', 1, 0, NULL, '', 'francois.devaux@gmail.com', 's3NYFrNfMIguqqyd/oLB1Q==', '2012-10-08 17:40:07.358873', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (31, 0, 31, '$2y$07$bzjNXiqxahasZivkL1fVSeNYftuDD1Dt5v0eYfVolfkE11/y14PwS', 'bcrypt', 'wYOfK3r7.nLf7xWR', 1, 0, NULL, '', 'jffsaquet@free.fr', '32.uHtbqjfaKDe/4nI1iuA==', '2012-10-08 17:41:02.763914', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (32, 0, 32, '$2y$07$T1PRZFbQSVntTkPTXSquKeYz5gri610zfe4LB8Smq09lQfaIt8zhy', 'bcrypt', 'WtSlwRQzoVdUeK02', 1, 0, NULL, '', 'bernard.mahe@thedstock.com', '2Dz/G7WhpaG0EsW7tScwDw==', '2012-10-08 17:42:23.535041', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (34, 0, 34, '$2y$07$aBXBbxXoKFTWPUzESyXTQ.A..ej4hm2ATvOp6bPznU4RdCMiU5Vl6', 'bcrypt', 'p6Cw6j0uXEmFSFUH', 1, 0, NULL, '', 's3b.rum@gmail.com', 'NKJOpxjPzSUlh5nAvkFTmA==', '2012-10-08 17:44:05.022517', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (35, 0, 35, '$2y$07$KBPKXTTlOyvwQk33SkfVWuMFJH1OYOyW8EFExP7pLtPlqDXIccu9W', 'bcrypt', '04LeUgCLrJnyRhWc', 1, 0, NULL, '', 'thomas.hahusseau@gmail.com', '9LLRWBkdZgF0FWmJ1Twwkg==', '2012-10-08 17:45:44.658596', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (20, 12, 20, '$2y$07$bSDqUkvWPSXLblLIP1LMYO/anL8zp9v56HqFURR8UH7ZNny03LcV.', 'bcrypt', 'uAlZlXEFMvsJGsNi', 1, 0, '2012-10-19 15:34:18.706609', 'paul+echoes@fariello.eu', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (7, 67, 7, '$2y$07$UVPWMRDPLh/pRkrjZzTiM.nHVO7OxacmbSvi/dwNVtKu3Lm.uiRAi', 'bcrypt', 'YtX91Q60kNkeoUd8', 1, 0, '2012-10-05 15:12:19.45331', 'louis@durufle.eu', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (9, 50, 9, '$2y$07$Zln3KB/MWlXVakbvXi3fYuIorP4GGVXCIWjrUWnF01DlSRujVhuhS', 'bcrypt', 'nzy00NbvWrgqfNak', 1, 0, '2012-10-20 16:57:25.247025', 'cyberval@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (11, 0, 11, '$2y$07$YzH3KzTjPSXmWTfMQ03Ya.mB9NvOE/X7iDpxV0tP2foTgxBnrK.uq', 'bcrypt', 'kRy3UeEFhaXNKnZp', 1, 0, NULL, '', 'jffsaquet@gmail.com', 'sgLgqIsAezhOlujTCoE3kQ==', '2012-09-16 15:13:13.653498', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (12, 13, 12, '$2y$07$QSPsLDTpZQ7zWU7IKVPXKOrA1bfLlsUgGIC96HwqXPmbG04M9cIWK', 'bcrypt', 'IDn4Ukm/uaoJ1tY1', 1, 0, '2012-10-18 23:17:48.749208', 'bertin.emilien@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (13, 11, 13, '$2y$07$KF/RQUy2YSHOaiStajn1WeP3ekelwcBOVLjvZIGSfZ/pKyiou3IIW', 'bcrypt', '0pSIm8iBPrE/rZwb', 1, 0, '2012-09-14 08:39:23.086517', 'baptiste.jacquemet@gmail.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (8, 30, 8, '$2y$07$MBTMbVfORjCyKTWuXiDEZ.ZuyZ.n02fB3HnpF6jHn3kg9/RJ.dp.m', 'bcrypt', '85NuxPNQ41V0fAFl', 1, 3, '2012-10-18 14:35:08.037515', 'sylvain.herledan_echoes@shadowz.sytes.net', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (10, 21, 10, '$2y$07$KxboPCTMSl.0QEnYJimtU.EFV/Xia0SV/PFI.IcqnDp7QQs.Jy7gq', 'bcrypt', '37jDENRp6HjZ.J/X', 1, 0, '2012-09-13 12:30:56.594681', 'alfred@huji.fr', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (3, 163, 3, '$2y$07$KUqtX0PFKFTrcEntY0rDU.2we1eSD79I0irzAh4wl2jFfvToSx4de', 'bcrypt', '1k/gdG0umxjokkEX', 1, 0, '2012-10-06 12:33:12.351462', 'florent.poinsaut@echoes-tech.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (4, 333, 4, '$2y$07$KUqtX0PFKFTrcEntY0rDU.2we1eSD79I0irzAh4wl2jFfvToSx4de', 'bcrypt', '1k/gdG0umxjokkEX', 1, 0, '2012-10-26 09:59:10.141984', 'thomas.saquet@echoes-tech.com', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (6, 277, 6, '$2y$07$bxbgbCjSO1jVTzX2LkvhSup4BqFP1CPnoXEr9Vx/7aB41jNkSx.By', 'bcrypt', 'w7btITCyWWVx6lcS', 1, 0, '2012-10-09 08:33:41.585189', 'chateaum+echoes@gmail.com', '', '', NULL, 1);


--
-- TOC entry 2436 (class 0 OID 49369)
-- Dependencies: 229 2435 2446
-- Data for Name: auth_identity; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (42, 0, 42, 'loginname', 'remi@reminoel.net');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (3, 0, 3, 'loginname', 'florent.poinsaut@echoes-tech.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (4, 0, 4, 'loginname', 'thomas.saquet@echoes-tech.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (6, 0, 6, 'loginname', 'chateaum+echoes@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (7, 0, 7, 'loginname', 'louis@durufle.eu');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (8, 0, 8, 'loginname', 'sylvain.herledan_echoes@shadowz.sytes.net');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (9, 0, 9, 'loginname', 'cyberval@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (10, 0, 10, 'loginname', 'alfred@huji.fr');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (11, 0, 11, 'loginname', 'jffsaquet@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (12, 0, 12, 'loginname', 'bertin.emilien@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (13, 0, 13, 'loginname', 'baptiste.jacquemet@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (17, 0, 17, 'loginname', 'benjamin.maze@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (18, 0, 18, 'loginname', 'julien.jordan@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (19, 0, 19, 'loginname', 'thomas.martelet@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (20, 0, 20, 'loginname', 'paul+echoes@fariello.eu');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (21, 0, 21, 'loginname', 'pyro853@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (27, 0, 27, 'loginname', 'poinsaut.philippe@wanadoo.fr');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (28, 0, 28, 'loginname', 'hinfray.guy@neuf.fr');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (29, 0, 29, 'loginname', 'sebastienviger@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (30, 0, 30, 'loginname', 'francois.devaux@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (31, 0, 31, 'loginname', 'jffsaquet@free.fr');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (32, 0, 32, 'loginname', 'bernard.mahe@thedstock.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (33, 0, 33, 'loginname', 'fettprodj@hotmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (34, 0, 34, 'loginname', 's3b.rum@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (35, 0, 35, 'loginname', 'thomas.hahusseau@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (38, 0, 38, 'loginname', 'romain.hinfray@echoes-tech.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (39, 0, 39, 'loginname', 'morgan.lamant@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (40, 0, 40, 'loginname', 'phenixnoir@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (41, 0, 41, 'loginname', 'xavier.mehrenberger@gmail.com');


--
-- TOC entry 2437 (class 0 OID 49385)
-- Dependencies: 231 2435 2446
-- Data for Name: auth_token; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (550, 0, 3, 'fIMcZ.KEUza.2ojrV1YLvQ==', '2012-10-01 11:21:49.030862');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (5, 0, 3, 'G8aPniWU2L3u1hUPbFbFGQ==', '2012-09-27 00:23:06.032625');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (552, 0, 3, 'H7JLr0GVlQPqRME7TL2qrw==', '2012-10-01 11:23:03.671532');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (553, 0, 9, 'YfZbuq8femsVpFF31.ef2Q==', '2012-10-01 11:48:55.179964');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (849, 0, 40, 'R13G29GUhE8hELo6xcqdCg==', '2012-10-25 13:07:45.392387');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (559, 0, 3, '6tS2IITpvn7ycHTtewELvw==', '2012-10-01 12:34:32.154405');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (561, 0, 4, 'DdvehhnaA32QZQkIeec7Vg==', '2012-10-01 12:35:53.564204');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (622, 0, 4, 'UCeSj6e4ndRQSF4hvxuG7Q==', '2012-10-02 15:25:45.996531');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (772, 0, 20, 'dY7XSUfT8IdT.isuE66zAw==', '2012-10-19 15:07:51.417043');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (774, 0, 20, 'IAa0af6CiP8i2gI6/Us5ew==', '2012-10-19 15:10:24.276143');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (778, 0, 7, '.w9uy6LB0jFXwComto/3YQ==', '2012-10-19 15:22:55.095429');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (858, 0, 38, 'OcJciPtDgqaIeaPoIhWF5g==', '2012-10-26 11:25:30.233386');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (631, 0, 18, '0ubd8g4G3lTu44bWyQXedA==', '2012-10-04 07:43:40.471104');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (635, 0, 4, 'bh1ygXXd47HhSuWElzzFHg==', '2012-10-04 09:30:37.588066');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (862, 0, 38, '/g1DXCUi3moKevzBA3GrtQ==', '2012-10-26 15:24:36.343028');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (637, 0, 7, '1emjnLPIFnUTNxeuczwlIQ==', '2012-10-04 11:40:24.01641');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (34, 0, 4, '3pNAkCVtqgIplwEy0tl8UA==', '2012-09-27 09:01:47.325999');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (639, 0, 4, '5yTrrfm2UoVyrp70QJVqXQ==', '2012-10-04 17:35:40.437832');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (640, 0, 3, 'YMnCU3k2Pm8J5r8JVaVSkg==', '2012-10-05 07:39:33.281458');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (718, 0, 3, 'kaa3SrI6rHFfHzG5HbkyWA==', '2012-10-12 07:28:33.261604');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (644, 0, 3, 'y6QBUMF8kQGATmMWSDegdg==', '2012-10-09 18:13:38.282883');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (787, 0, 38, 'c67vKMmD..kCEEww8HaE3Q==', '2012-10-20 09:19:32.245095');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (721, 0, 3, '1wQ/z8F9AKwqZMXJED7B6g==', '2012-10-12 16:28:45.311966');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (722, 0, 6, 'nYFpIphVPhOStbQLYqz25g==', '2012-10-12 16:58:47.553704');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (589, 0, 4, '6Xj3Fhvd1EfKB3p97BPkkw==', '2012-10-01 23:21:29.461682');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (650, 0, 3, 'z2YfbB6hIbVsUI9KZ.bD3A==', '2012-10-09 18:17:32.10024');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (869, 0, 18, 'eGrYluXbEaUOXtmvJLr5oA==', '2012-10-29 13:41:59.089799');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (595, 0, 4, 'bAIIgzD1slVSBpXG0XmiUw==', '2012-10-01 23:26:18.034887');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (727, 0, 7, 'CVIJkWY75JEFdKKAFu83ag==', '2012-10-15 07:25:33.051263');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (656, 0, 3, 'fAdTROH9.5UFEMNAqqoIfw==', '2012-10-09 18:20:34.716211');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (657, 0, 4, 'kGOnOCxwMb9e2/ZCPcB7Pg==', '2012-10-09 18:20:52.272939');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (733, 0, 4, '2pHPSs2cAnR7AY22sL/ONQ==', '2012-10-16 14:02:34.508228');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (661, 0, 3, 'B/v1q31SEesVQQ2i1wmfEQ==', '2012-10-09 18:22:20.344865');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (877, 0, 38, 'daa45x7ozUMugNhNmbuZQA==', '2012-10-30 09:32:58.437461');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (738, 0, 3, 'qUsYm0zqD6xa21vjxarskQ==', '2012-10-17 06:58:31.220202');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (800, 0, 3, 'yS9Wci1tbo5Smo2x6NOhHg==', '2012-10-20 12:31:47.300508');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (665, 0, 4, 'b4fWvUovCIMrPtCwdyOEuw==', '2012-10-09 18:33:47.000478');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (666, 0, 4, 'WVqHxUylHIyqEfo8a4UwhQ==', '2012-10-09 18:33:54.19768');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (743, 0, 17, '6y4KSt.Fj9NEuOW6A8m3XA==', '2012-10-17 08:19:30.411135');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (804, 0, 38, '6araRWHplvtqC6aHQ6iUOQ==', '2012-10-20 14:38:02.84048');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (883, 0, 38, 'OthIjQAmiJwMXbStMx/XJQ==', '2012-11-01 13:28:32.711669');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (673, 0, 4, 'Bov.1JLFggcXTEwdUd1JuA==', '2012-10-09 20:33:17.451898');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (746, 0, 19, 'lq2gDEKi60i9kPov/eeZCQ==', '2012-10-17 09:17:59.535444');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (808, 0, 38, 'AyIfcwILREW/5yO3MeOlpw==', '2012-10-20 15:06:49.053859');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (815, 0, 4, 'blAyzDgdufqtjdm.ND0CPA==', '2012-10-20 15:40:19.242691');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (756, 0, 6, 'cKJldoKuu1kGAbUhAujuNw==', '2012-10-19 09:27:20.772908');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (898, 0, 20, '6rZqrBJnLvggxtgHuE6JiQ==', '2012-11-06 09:02:20.704749');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (825, 0, 21, 'c3g7rXGDBigBBvoeZqniXA==', '2012-10-21 14:23:46.176994');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (826, 0, 17, 'MKDLA0UI/7c/WlyKM/V/GA==', '2012-10-22 07:09:20.700425');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (832, 0, 38, '.iTZIAHfHEn96PXCx.oAEw==', '2012-10-22 10:35:01.366507');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (905, 0, 6, 'sg/z170GV62A0MYRUNwAYg==', '2012-11-07 10:18:25.711456');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (834, 0, 38, '8HbeT2sr91cqC9RVg4wP3g==', '2012-10-22 13:47:43.535347');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (907, 0, 19, '974e0qXvwpd9y8Q6e4Tsag==', '2012-11-08 10:01:33.151095');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (908, 0, 3, 'nwr4./aEbrc2PlCE0.dcVw==', '2012-11-08 15:13:53.673339');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (909, 0, 4, '8rqBKI4brwhtrDndAS8dwg==', '2012-11-09 09:59:10.147385');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (99, 0, 6, '6RZTVHWAFfOTnz9Ra1UOAw==', '2012-09-27 09:59:32.776988');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (102, 0, 7, 'b3rmmXVc1lp93Ecg3TlYAA==', '2012-09-27 10:00:45.863651');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (103, 0, 8, 'hW.dh2lyCTVxxqN.efvKaw==', '2012-09-27 10:00:48.332579');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (104, 0, 4, 'AVkG0qkpjrxtNUPaeX.Pig==', '2012-09-27 10:03:22.301355');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (144, 0, 3, '283gM8loxHXEKf7lWT69DA==', '2012-09-27 11:51:30.843337');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (163, 0, 10, '7nOL90.q/h1rvH/Ow0XgFw==', '2012-09-27 12:44:10.831373');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (182, 0, 4, 'cckRARFgy/WbDgf9zk1oOw==', '2012-09-27 14:03:41.242165');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (276, 0, 9, '3jL.BZeugejApFwAfUILXg==', '2012-09-27 18:32:29.837069');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (290, 0, 9, 'jZz2uUgBst8oG8Y27QUg2w==', '2012-09-27 19:06:48.841854');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (370, 0, 6, 'TrpzfLksg9djPhRutKmSMQ==', '2012-09-27 22:28:45.50984');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (384, 0, 12, 'b8D5x758b2LXkx.ZH6k68g==', '2012-09-27 23:04:14.09465');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (400, 0, 13, 'VPu29wKx6q.C32Ln1yYWvw==', '2012-09-28 08:47:59.647278');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (479, 0, 8, 'O0MVneGKyIzBdZ8z.8c06Q==', '2012-09-28 14:35:48.93408');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (499, 0, 10, 'u8bTyAMHxlgOe5gs15FZxQ==', '2012-09-28 23:56:36.081845');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (519, 0, 4, 'cK8HDKGyjoFESh3z8yXY/g==', '2012-10-01 09:09:02.224095');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (520, 0, 4, 'rHcPOc8Xdt5pqPmw1Ew6cw==', '2012-10-01 09:10:33.496749');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (527, 0, 3, 'OY41hXI0/ZNpQb85dNTXEA==', '2012-10-01 09:15:34.84708');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (528, 0, 4, 'NJ.WqvUiHdwFuxhOGo8qJg==', '2012-10-01 09:16:23.649036');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (529, 0, 3, 'uOV/pINRAUejkeeYzQA3nQ==', '2012-10-01 09:22:34.436392');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (541, 0, 4, 'EFVwNxQ0APechzQkLXYWYA==', '2012-10-01 10:05:22.471906');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (543, 0, 4, '0qciV6Nn1BnHdgsJNMnGHg==', '2012-10-01 10:52:18.692107');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (544, 0, 3, 'tO/UBJho/O.y0FgD0n5ucw==', '2012-10-01 11:06:45.664899');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (547, 0, 3, '9NKZbXkn6AOjs/igRiEEWQ==', '2012-10-01 11:14:15.843231');


-- Completed on 2012-10-28 19:39:46 CET

--
-- PostgreSQL database dump complete
--


--
-- PostgreSQL database dump
--

-- Dumped from database version 8.4.13
-- Dumped by pg_dump version 9.1.5
-- Started on 2012-09-11 19:22:00 CEST

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

SET search_path = public, pg_catalog;

--
-- TOC entry 2414 (class 0 OID 0)
-- Dependencies: 142
-- Name: T_ADDON_ADO_ADO_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ADDON_ADO_ADO_ID_seq"', 5, true);


--
-- TOC entry 2415 (class 0 OID 0)
-- Dependencies: 192
-- Name: T_ALERT_ACKNOWLEDGE_ACK_ACK_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_ACKNOWLEDGE_ACK_ACK_ID_seq"', 1, false);


--
-- TOC entry 2416 (class 0 OID 0)
-- Dependencies: 183
-- Name: T_ALERT_ALE_ALE_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_ALE_ALE_ID_seq"', 2, true);


--
-- TOC entry 2417 (class 0 OID 0)
-- Dependencies: 153
-- Name: T_ALERT_CRITERIA_ACR_ACR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_CRITERIA_ACR_ACR_ID_seq"', 1, false);


--
-- TOC entry 2418 (class 0 OID 0)
-- Dependencies: 179
-- Name: T_ALERT_SEQUENCE_ASE_ASE_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_SEQUENCE_ASE_ASE_ID_seq"', 1, false);


--
-- TOC entry 2419 (class 0 OID 0)
-- Dependencies: 185
-- Name: T_ALERT_TRACKING_ATR_ATR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_TRACKING_ATR_ATR_ID_seq"', 3279, true);


--
-- TOC entry 2420 (class 0 OID 0)
-- Dependencies: 210
-- Name: T_ALERT_TRACKING_EVENT_ATE_ATE_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_TRACKING_EVENT_ATE_ATE_ID_seq"', 1, false);


--
-- TOC entry 2421 (class 0 OID 0)
-- Dependencies: 155
-- Name: T_ALERT_VALUE_AVA_AVA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_VALUE_AVA_AVA_ID_seq"', 2, true);


--
-- TOC entry 2422 (class 0 OID 0)
-- Dependencies: 196
-- Name: T_ASSET_AST_AST_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ASSET_AST_AST_ID_seq"', 1, false);


--
-- TOC entry 2423 (class 0 OID 0)
-- Dependencies: 181
-- Name: T_ENGINE_ENG_ENG_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ENGINE_ENG_ENG_ID_seq"', 3, true);


--
-- TOC entry 2424 (class 0 OID 0)
-- Dependencies: 216
-- Name: T_INFORMATION_HISTORICAL_VALUE_IHV_IHV_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_HISTORICAL_VALUE_IHV_IHV_ID_seq"', 1, false);


--
-- TOC entry 2425 (class 0 OID 0)
-- Dependencies: 148
-- Name: T_INFORMATION_UNIT_TYPE_UTY_IUT_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_UNIT_TYPE_UTY_IUT_ID_seq"', 2, true);


--
-- TOC entry 2426 (class 0 OID 0)
-- Dependencies: 150
-- Name: T_INFORMATION_UNIT_UNT_INU_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_UNIT_UNT_INU_ID_seq"', 1, false);


--
-- TOC entry 2427 (class 0 OID 0)
-- Dependencies: 200
-- Name: T_INFORMATION_VALUE_IVA_IVA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_VALUE_IVA_IVA_ID_seq"', 39615, true);


--
-- TOC entry 2428 (class 0 OID 0)
-- Dependencies: 157
-- Name: T_MEDIA_MED_MED_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_MEDIA_MED_MED_ID_seq"', 2, true);


--
-- TOC entry 2429 (class 0 OID 0)
-- Dependencies: 171
-- Name: T_MEDIA_VALUE_MEV_MEV_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_MEDIA_VALUE_MEV_MEV_ID_seq"', 6, true);


--
-- TOC entry 2430 (class 0 OID 0)
-- Dependencies: 173
-- Name: T_OPTION_OPT_OPT_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_OPTION_OPT_OPT_ID_seq"', 2, true);


--
-- TOC entry 2431 (class 0 OID 0)
-- Dependencies: 207
-- Name: T_ORGANIZATION_FIELD_OFI_OFI_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ORGANIZATION_FIELD_OFI_OFI_ID_seq"', 1, false);


--
-- TOC entry 2432 (class 0 OID 0)
-- Dependencies: 165
-- Name: T_ORGANIZATION_ORG_ORG_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ORGANIZATION_ORG_ORG_ID_seq"', 5, true);


--
-- TOC entry 2433 (class 0 OID 0)
-- Dependencies: 163
-- Name: T_ORGANIZATION_TYPE_OTY_OTY_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ORGANIZATION_TYPE_OTY_OTY_ID_seq"', 1, false);


--
-- TOC entry 2434 (class 0 OID 0)
-- Dependencies: 161
-- Name: T_PACK_PCK_PCK_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_PACK_PCK_PCK_ID_seq"', 1, true);


--
-- TOC entry 2435 (class 0 OID 0)
-- Dependencies: 140
-- Name: T_PLUGIN_PLG_PLG_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_PLUGIN_PLG_PLG_ID_seq"', 1, false);


--
-- TOC entry 2436 (class 0 OID 0)
-- Dependencies: 194
-- Name: T_PROBE_PRB_PRB_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_PROBE_PRB_PRB_ID_seq"', 1, false);


--
-- TOC entry 2437 (class 0 OID 0)
-- Dependencies: 188
-- Name: T_SEARCH_PARAMETER_SEP_SEP_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SEARCH_PARAMETER_SEP_SEP_ID_seq"', 1, true);


--
-- TOC entry 2438 (class 0 OID 0)
-- Dependencies: 145
-- Name: T_SEARCH_TYPE_STY_STY_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SEARCH_TYPE_STY_STY_ID_seq"', 1, true);


--
-- TOC entry 2439 (class 0 OID 0)
-- Dependencies: 190
-- Name: T_SOURCE_PARAMETER_SRP_SRP_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SOURCE_PARAMETER_SRP_SRP_ID_seq"', 1, true);


--
-- TOC entry 2440 (class 0 OID 0)
-- Dependencies: 202
-- Name: T_SPACE_SPA_SPA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SPACE_SPA_SPA_ID_seq"', 1, false);


--
-- TOC entry 2441 (class 0 OID 0)
-- Dependencies: 198
-- Name: T_SYSLOG_SLO_SLO_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SYSLOG_SLO_SLO_ID_seq"', 57244, true);


--
-- TOC entry 2442 (class 0 OID 0)
-- Dependencies: 176
-- Name: T_USER_ACTION_ACT_UAC_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_ACTION_ACT_UAC_ID_seq"', 1, false);


--
-- TOC entry 2443 (class 0 OID 0)
-- Dependencies: 218
-- Name: T_USER_FIELD_UFI_UFI_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_FIELD_UFI_UFI_ID_seq"', 1, false);


--
-- TOC entry 2444 (class 0 OID 0)
-- Dependencies: 214
-- Name: T_USER_HISTORICAL_ACTION_UHA_UHA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_HISTORICAL_ACTION_UHA_UHA_ID_seq"', 1, false);


--
-- TOC entry 2445 (class 0 OID 0)
-- Dependencies: 167
-- Name: T_USER_PROFILE_UPR_UPR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_PROFILE_UPR_UPR_ID_seq"', 1, false);


--
-- TOC entry 2446 (class 0 OID 0)
-- Dependencies: 204
-- Name: T_USER_RIGHT_URI_URI_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_RIGHT_URI_URI_ID_seq"', 1, false);


--
-- TOC entry 2447 (class 0 OID 0)
-- Dependencies: 159
-- Name: T_USER_ROLE_URO_URO_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_ROLE_URO_URO_ID_seq"', 1, false);


--
-- TOC entry 2448 (class 0 OID 0)
-- Dependencies: 169
-- Name: T_USER_USR_USR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_USR_USR_ID_seq"', 5, true);


--
-- TOC entry 2449 (class 0 OID 0)
-- Dependencies: 223
-- Name: auth_identity_id_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('auth_identity_id_seq', 8, true);


--
-- TOC entry 2450 (class 0 OID 0)
-- Dependencies: 221
-- Name: auth_info_id_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('auth_info_id_seq', 13, true);


--
-- TOC entry 2451 (class 0 OID 0)
-- Dependencies: 225
-- Name: auth_token_id_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('auth_token_id_seq', 155, true);


--
-- TOC entry 2361 (class 0 OID 38809)
-- Dependencies: 154 2410
-- Data for Name: T_ALERT_CRITERIA_ACR; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (1, 0, 'lt', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (2, 0, 'le', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (3, 0, 'eq', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (4, 0, 'ne', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (5, 0, 'ge', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (6, 0, 'gt', NULL);


--
-- TOC entry 2358 (class 0 OID 38764)
-- Dependencies: 149 2410
-- Data for Name: T_INFORMATION_UNIT_TYPE_UTY; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_UNIT_TYPE_UTY" ("IUT_ID", version, "IUT_NAME", "IUT_DELETE") VALUES (1, 0, 'text', NULL);
INSERT INTO "T_INFORMATION_UNIT_TYPE_UTY" ("IUT_ID", version, "IUT_NAME", "IUT_DELETE") VALUES (2, 0, 'number', NULL);


--
-- TOC entry 2405 (class 0 OID 39520)
-- Dependencies: 230 2361 2358 2410
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
-- TOC entry 2354 (class 0 OID 38709)
-- Dependencies: 143 2410
-- Data for Name: T_ADDON_ADO; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (2, 0, 'file', NULL);


--
-- TOC entry 2381 (class 0 OID 39124)
-- Dependencies: 191 2410
-- Data for Name: T_SOURCE_PARAMETER_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (1, 0, 'text', 'path', NULL);


--
-- TOC entry 2406 (class 0 OID 39537)
-- Dependencies: 231 2381 2354 2410
-- Data for Name: TJ_ADO_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (1, 2);


--
-- TOC entry 2366 (class 0 OID 38874)
-- Dependencies: 164 2410
-- Data for Name: T_ORGANIZATION_TYPE_OTY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2365 (class 0 OID 38863)
-- Dependencies: 162 2410
-- Data for Name: T_PACK_PCK; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PACK_PCK" ("PCK_ID", version, "PCK_NAME", "PCK_DELETE") VALUES (1, 0, 'alpha', NULL);


--
-- TOC entry 2367 (class 0 OID 38885)
-- Dependencies: 166 2365 2366 2410
-- Data for Name: T_ORGANIZATION_ORG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (4, 0, 'cheyenne', 'montigny', '78', 'yoyo', NULL, 1, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (5, 0, '', '', '', 'Technologies', NULL, NULL, NULL);


--
-- TOC entry 2383 (class 0 OID 39156)
-- Dependencies: 195 2367 2410
-- Data for Name: T_PROBE_PRB; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PROBE_PRB" ("PRB_ID", version, "PRB_CERT", "PRB_NAME", "PRB_DELETE", "PRB_ORG_ORG_ID") VALUES (6585, 0, 'temp', 'rhi-laptop-ea-probe', NULL, 4);


--
-- TOC entry 2384 (class 0 OID 39172)
-- Dependencies: 197 2383 2410
-- Data for Name: T_ASSET_AST; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ASSET_AST" ("AST_ID", version, "AST_NAME", "AST_DELETE", "AST_IS_HOST", "AST_PRB_PRB_ID") VALUES (1, 0, 'rhi-laptop', NULL, true, 6585);


--
-- TOC entry 2353 (class 0 OID 38698)
-- Dependencies: 141 2410
-- Data for Name: T_PLUGIN_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (1, 0, 'Debian 6.0 - System - Test', 'System', NULL);


--
-- TOC entry 2409 (class 0 OID 39588)
-- Dependencies: 234 2384 2353 2410
-- Data for Name: TJ_AST_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_AST_PLG" ("T_ASSET_AST_AST_ID", "T_PLUGIN_PLG_PLG_ID") VALUES (1, 1);


--
-- TOC entry 2359 (class 0 OID 38775)
-- Dependencies: 151 2358 2410
-- Data for Name: T_INFORMATION_UNIT_UNT; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (3, 0, 'name', 'name', NULL, 1);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (0, 0, 'Kilo Bytes', 'Kb', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (1, 0, 'Packets', 'Pkts', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (2, 0, 'Bytes', 'Bytes', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (4, 0, 'load', 'load', NULL, 2);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (5, 0, 'Time in USER_Hz', 'time in USER_Hz', NULL, 2);


--
-- TOC entry 2356 (class 0 OID 38735)
-- Dependencies: 146 2410
-- Data for Name: T_SEARCH_TYPE_STY; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_TYPE_STY" ("STY_ID", version, "STY_NAME", "STY_DELETE") VALUES (1, 0, 'regex', NULL);


--
-- TOC entry 2355 (class 0 OID 38718)
-- Dependencies: 144 2353 2354 2410
-- Data for Name: T_SOURCE_SRC; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 1, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 2, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 3, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 4, 1, 2);


--
-- TOC entry 2357 (class 0 OID 38744)
-- Dependencies: 147 2355 2356 2410
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


--
-- TOC entry 2360 (class 0 OID 38789)
-- Dependencies: 152 2357 2359 2410
-- Data for Name: T_INFORMATION_INF; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'CPU name', NULL, 1, 4, 1, 1, 3);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory free', NULL, 2, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Network interface name', NULL, 1, 2, 1, 1, 3);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Total Memory', NULL, 1, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Buffers', NULL, 3, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory cached', NULL, 4, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory Swap size', NULL, 5, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory Swap free', NULL, 6, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Receive bytes', NULL, 1, 2, 1, 2, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Receive packets', NULL, 1, 2, 1, 3, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Receive errors', NULL, 1, 2, 1, 4, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Receive drops', NULL, 1, 2, 1, 5, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Transmit bytes', NULL, 1, 2, 1, 6, 2);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Transmit packets', NULL, 1, 2, 1, 7, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Transmit errors', NULL, 1, 2, 1, 8, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Transmit drop', NULL, 1, 2, 1, 9, 1);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Load average on 1 minute', NULL, 1, 3, 1, 1, 4);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Load average on 5 minutes', NULL, 1, 3, 1, 2, 4);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Load average on 15 minutes', NULL, 1, 3, 1, 3, 4);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'user mode CPU usage', NULL, 1, 4, 1, 2, 5);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'user mode with low priority CPU usage', NULL, 1, 4, 1, 3, 5);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'system mode CPU usage', NULL, 1, 4, 1, 4, 5);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'inactive mode CPU usage', NULL, 1, 4, 1, 5, 5);


--
-- TOC entry 2362 (class 0 OID 38820)
-- Dependencies: 156 2360 2361 2410
-- Data for Name: T_ALERT_VALUE_AVA; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ALERT_VALUE_AVA" ("AVA_ID", version, "AVA_KEY_VALUE", "AVA_VALUE", "AVA_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "AVA_ACR_ACR_ID") VALUES (1, 0, NULL, '4762924', NULL, 2, 1, 1, 1, 1);
INSERT INTO "T_ALERT_VALUE_AVA" ("AVA_ID", version, "AVA_KEY_VALUE", "AVA_VALUE", "AVA_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "AVA_ACR_ACR_ID") VALUES (2, 0, NULL, '0.5', NULL, 1, 3, 1, 1, 5);


--
-- TOC entry 2375 (class 0 OID 39022)
-- Dependencies: 180 2362 2410
-- Data for Name: T_ALERT_SEQUENCE_ASE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2376 (class 0 OID 39040)
-- Dependencies: 182 2410
-- Data for Name: T_ENGINE_ENG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ENGINE_ENG" ("ENG_ID", version, "ENG_FQDN", "ENG_STATE", "ENG_DELETE", "ENG_KEEP_ALIVE", "ENG_NB_THREAD") VALUES (3, 0, 'engine', '0', NULL, NULL, 100);


--
-- TOC entry 2377 (class 0 OID 39051)
-- Dependencies: 184 2362 2375 2376 2410
-- Data for Name: T_ALERT_ALE; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ALERT_ALE" ("ALE_ID", version, "ALE_NAME", "ALE_CREA_DATE", "ALE_DELETE", "ALE_LAST_ATTEMPT", "ALE_THREAD_SLEEP", "ALE_AVA_AVA_ID", "ASE_FIRST_ID_ASE_ID", "ALE_ENG_ENG_ID") VALUES (2, 3, 'surcharge système', '2012-09-12 18:40:20', NULL, '2012-09-11 17:16:23.834179', 0, 2, NULL, 3);
INSERT INTO "T_ALERT_ALE" ("ALE_ID", version, "ALE_NAME", "ALE_CREA_DATE", "ALE_DELETE", "ALE_LAST_ATTEMPT", "ALE_THREAD_SLEEP", "ALE_AVA_AVA_ID", "ASE_FIRST_ID_ASE_ID", "ALE_ENG_ENG_ID") VALUES (1, 76, 'occupation mémoire', '2012-09-08 23:48:24', NULL, '2012-09-11 17:16:23.836697', 0, 1, NULL, 3);


--
-- TOC entry 2363 (class 0 OID 38841)
-- Dependencies: 158 2410
-- Data for Name: T_MEDIA_MED; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_MEDIA_MED" ("MED_ID", version, "MED_NAME", "MED_DELETE") VALUES (1, 0, 'mail', NULL);
INSERT INTO "T_MEDIA_MED" ("MED_ID", version, "MED_NAME", "MED_DELETE") VALUES (2, 0, 'sms', NULL);


--
-- TOC entry 2368 (class 0 OID 38906)
-- Dependencies: 168 2410
-- Data for Name: T_USER_PROFILE_UPR; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2364 (class 0 OID 38852)
-- Dependencies: 160 2410
-- Data for Name: T_USER_ROLE_URO; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2369 (class 0 OID 38917)
-- Dependencies: 170 2364 2367 2368 2410
-- Data for Name: T_USER_USR; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (3, 0, 'Romain', 'hinfray', 'neorom@gmail.com', '', NULL, NULL, 4, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "CURRENT_ORG_ID", "USR_UPR_UPR_ID") VALUES (5, 0, 'ECHOES', 'Technologies', 'contact@echoes-tech.com', '', NULL, NULL, NULL, NULL);


--
-- TOC entry 2370 (class 0 OID 38943)
-- Dependencies: 172 2363 2369 2410
-- Data for Name: T_MEDIA_VALUE_MEV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_MEDIA_VALUE_MEV" ("MEV_ID", version, "MEV_VALUE", "MEV_DELETE", "MEV_LAST_SEND", "MEV_NOTIF_END_OF_ALERT", "MEV_SNOOZE", "MEV_MED_MED_ID", "MEV_USR_USR_ID") VALUES (2, 21, 'neorom@gmail.com', NULL, '2012-09-11 17:18:51.243814', false, 60, 1, 3);
INSERT INTO "T_MEDIA_VALUE_MEV" ("MEV_ID", version, "MEV_VALUE", "MEV_DELETE", "MEV_LAST_SEND", "MEV_NOTIF_END_OF_ALERT", "MEV_SNOOZE", "MEV_MED_MED_ID", "MEV_USR_USR_ID") VALUES (6, 8, '+33607874128', NULL, '2012-09-11 17:19:14.894232', false, 10, 2, 3);


--
-- TOC entry 2402 (class 0 OID 39469)
-- Dependencies: 227 2370 2377 2410
-- Data for Name: TJ_MEV_ALE; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_MEV_ALE" ("T_MEDIA_VALUE_MEV_MEV_ID", "T_ALERT_ALE_ALE_ID") VALUES (6, 1);
INSERT INTO "TJ_MEV_ALE" ("T_MEDIA_VALUE_MEV_MEV_ID", "T_ALERT_ALE_ALE_ID") VALUES (2, 2);
INSERT INTO "TJ_MEV_ALE" ("T_MEDIA_VALUE_MEV_MEV_ID", "T_ALERT_ALE_ALE_ID") VALUES (6, 2);


--
-- TOC entry 2390 (class 0 OID 39272)
-- Dependencies: 208 2410
-- Data for Name: T_ORGANIZATION_FIELD_OFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2407 (class 0 OID 39554)
-- Dependencies: 232 2366 2390 2410
-- Data for Name: TJ_OFI_OTY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2380 (class 0 OID 39113)
-- Dependencies: 189 2410
-- Data for Name: T_SEARCH_PARAMETER_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_PARAMETER_SEP" ("SEP_ID", version, "SEP_FORMAT", "SEP_NAME", "SEP_DELETE") VALUES (1, 0, 'text', 'regex', NULL);


--
-- TOC entry 2403 (class 0 OID 39486)
-- Dependencies: 228 2356 2380 2410
-- Data for Name: TJ_STY_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_STY_SEP" ("T_SEARCH_TYPE_STY_STY_ID", "T_SEARCH_PARAMETER_SEP_SEP_ID") VALUES (1, 1);


--
-- TOC entry 2404 (class 0 OID 39503)
-- Dependencies: 229 2367 2369 2410
-- Data for Name: TJ_USR_ORG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (4, 3);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (5, 5);


--
-- TOC entry 2397 (class 0 OID 39397)
-- Dependencies: 219 2410
-- Data for Name: T_USER_FIELD_UFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2408 (class 0 OID 39571)
-- Dependencies: 233 2369 2397 2410
-- Data for Name: TJ_USR_UFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2387 (class 0 OID 39230)
-- Dependencies: 203 2410
-- Data for Name: T_SPACE_SPA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2388 (class 0 OID 39241)
-- Dependencies: 205 2410
-- Data for Name: T_USER_RIGHT_URI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2389 (class 0 OID 39250)
-- Dependencies: 206 2387 2368 2388 2410
-- Data for Name: T_ACCESS_CONTROL_LIST_ACL; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2382 (class 0 OID 39135)
-- Dependencies: 193 2377 2369 2410
-- Data for Name: T_ALERT_ACKNOWLEDGE_ACK; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2378 (class 0 OID 39077)
-- Dependencies: 186 2370 2377 2410
-- Data for Name: T_ALERT_TRACKING_ATR; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2392 (class 0 OID 39301)
-- Dependencies: 211 2378 2410
-- Data for Name: T_ALERT_TRACKING_EVENT_ATE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2385 (class 0 OID 39188)
-- Dependencies: 199 2383 2410
-- Data for Name: T_SYSLOG_SLO; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2396 (class 0 OID 39371)
-- Dependencies: 217 2384 2385 2360 2410
-- Data for Name: T_INFORMATION_HISTORICAL_VALUE_IHV; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2386 (class 0 OID 39204)
-- Dependencies: 201 2384 2385 2360 2410
-- Data for Name: T_INFORMATION_VALUE_IVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2371 (class 0 OID 38964)
-- Dependencies: 174 2410
-- Data for Name: T_OPTION_OPT; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_OPTION_OPT" ("OPT_ID", version, "OPT_NAME", "OPT_DELETE") VALUES (2, 0, 'quotasms', NULL);


--
-- TOC entry 2374 (class 0 OID 39002)
-- Dependencies: 178 2371 2367 2410
-- Data for Name: T_OPTION_VALUE_OPV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_OPTION_VALUE_OPV" (version, "OPV_VALUE", "OPV_DELETE", "OPT_ID_OPT_ID", "ORG_ID_ORG_ID") VALUES (20, '10', NULL, 2, 4);


--
-- TOC entry 2391 (class 0 OID 39281)
-- Dependencies: 209 2390 2367 2410
-- Data for Name: T_ORGANIZATION_VALUE_OVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2372 (class 0 OID 38973)
-- Dependencies: 175 2365 2371 2410
-- Data for Name: T_PACK_OPTION_POP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PACK_OPTION_POP" (version, "POP_VALUE", "POP_DELETE", "PCK_ID_PCK_ID", "OPT_ID_OPT_ID") VALUES (0, '10', NULL, 1, 2);


--
-- TOC entry 2393 (class 0 OID 39315)
-- Dependencies: 212 2357 2380 2410
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


--
-- TOC entry 2394 (class 0 OID 39333)
-- Dependencies: 213 2381 2355 2410
-- Data for Name: T_SOURCE_PARAMETER_VALUE_SPV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/meminfo', NULL, 1, 1, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/net/dev', NULL, 1, 2, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/loadavg', NULL, 1, 3, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/stat', NULL, 1, 4, 1);


--
-- TOC entry 2373 (class 0 OID 38993)
-- Dependencies: 177 2410
-- Data for Name: T_USER_ACTION_ACT; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2379 (class 0 OID 39096)
-- Dependencies: 187 2369 2369 2410
-- Data for Name: T_USER_HIERARCHY_UHI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2395 (class 0 OID 39353)
-- Dependencies: 215 2369 2373 2410
-- Data for Name: T_USER_HISTORICAL_ACTION_UHA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2398 (class 0 OID 39406)
-- Dependencies: 220 2369 2397 2410
-- Data for Name: T_USER_VALUE_UVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2399 (class 0 OID 39426)
-- Dependencies: 222 2369 2410
-- Data for Name: auth_info; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (11, 0, NULL, '$2y$07$aT/jWz/0ay3ERkvsQyz/UOCWuhuI8lygpVamcAjG4AdfMjBqiGzrS', 'bcrypt', 'qPecPvsNFNlnKMAY', 1, 0, NULL, '', 'contact@echoes-tech.com', '', '2012-09-12 18:30:23.454545', 0);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (13, 3, 5, '$2y$07$KUqtX0PFKFTrcEntY0rDU.2we1eSD79I0irzAh4wl2jFfvToSx4de', 'bcrypt', '1k/gdG0umxjokkEX', 1, 0, '2012-09-11 16:52:53.097319', '', 'contact@echoes-tech.com', 'ZOMRN0b1sy5MuMGX.3ny7g==', '2012-09-14 16:44:52.613662', 0);


--
-- TOC entry 2400 (class 0 OID 39442)
-- Dependencies: 224 2399 2410
-- Data for Name: auth_identity; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (6, 0, 11, 'loginname', 'ECHOES Technologies');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (8, 0, 13, 'loginname', 'contact@echoes-tech.com');


--
-- TOC entry 2401 (class 0 OID 39458)
-- Dependencies: 226 2399 2410
-- Data for Name: auth_token; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (155, 0, 13, '1ymtmylE82j4OpoCmR.Bww==', '2012-09-25 16:56:35.900922');


-- Completed on 2012-09-11 19:22:01 CEST

--
-- PostgreSQL database dump complete
--


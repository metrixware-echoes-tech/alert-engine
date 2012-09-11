--
-- PostgreSQL database dump
--

-- Dumped from database version 8.4.13
-- Dumped by pg_dump version 9.1.5
-- Started on 2012-09-11 01:06:02 CEST

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

SET search_path = public, pg_catalog;

--
-- TOC entry 2404 (class 0 OID 0)
-- Dependencies: 142
-- Name: T_ADDON_ADO_ADO_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ADDON_ADO_ADO_ID_seq"', 1, false);


--
-- TOC entry 2405 (class 0 OID 0)
-- Dependencies: 188
-- Name: T_ALERT_ACKNOWLEDGE_ACK_ACK_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_ACKNOWLEDGE_ACK_ACK_ID_seq"', 1, false);


--
-- TOC entry 2406 (class 0 OID 0)
-- Dependencies: 179
-- Name: T_ALERT_ALE_ALE_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_ALE_ALE_ID_seq"', 1, false);


--
-- TOC entry 2407 (class 0 OID 0)
-- Dependencies: 153
-- Name: T_ALERT_CRITERIA_ACR_ACR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_CRITERIA_ACR_ACR_ID_seq"', 1, false);


--
-- TOC entry 2408 (class 0 OID 0)
-- Dependencies: 175
-- Name: T_ALERT_SEQUENCE_ASE_ASE_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_SEQUENCE_ASE_ASE_ID_seq"', 1, false);


--
-- TOC entry 2409 (class 0 OID 0)
-- Dependencies: 181
-- Name: T_ALERT_TRACKING_ATR_ATR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_TRACKING_ATR_ATR_ID_seq"', 3126, true);


--
-- TOC entry 2410 (class 0 OID 0)
-- Dependencies: 206
-- Name: T_ALERT_TRACKING_EVENT_ATE_ATE_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_TRACKING_EVENT_ATE_ATE_ID_seq"', 1, false);


--
-- TOC entry 2411 (class 0 OID 0)
-- Dependencies: 155
-- Name: T_ALERT_VALUE_AVA_AVA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ALERT_VALUE_AVA_AVA_ID_seq"', 1, false);


--
-- TOC entry 2412 (class 0 OID 0)
-- Dependencies: 192
-- Name: T_ASSET_AST_AST_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ASSET_AST_AST_ID_seq"', 1, false);


--
-- TOC entry 2413 (class 0 OID 0)
-- Dependencies: 177
-- Name: T_ENGINE_ENG_ENG_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ENGINE_ENG_ENG_ID_seq"', 1, false);


--
-- TOC entry 2414 (class 0 OID 0)
-- Dependencies: 212
-- Name: T_INFORMATION_HISTORICAL_VALUE_IHV_IHV_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_HISTORICAL_VALUE_IHV_IHV_ID_seq"', 1, false);


--
-- TOC entry 2415 (class 0 OID 0)
-- Dependencies: 148
-- Name: T_INFORMATION_UNIT_TYPE_UTY_IUT_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_UNIT_TYPE_UTY_IUT_ID_seq"', 1, false);


--
-- TOC entry 2416 (class 0 OID 0)
-- Dependencies: 150
-- Name: T_INFORMATION_UNIT_UNT_INU_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_UNIT_UNT_INU_ID_seq"', 1, false);


--
-- TOC entry 2417 (class 0 OID 0)
-- Dependencies: 196
-- Name: T_INFORMATION_VALUE_IVA_IVA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_INFORMATION_VALUE_IVA_IVA_ID_seq"', 36626, true);


--
-- TOC entry 2418 (class 0 OID 0)
-- Dependencies: 157
-- Name: T_MEDIA_MED_MED_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_MEDIA_MED_MED_ID_seq"', 1, false);


--
-- TOC entry 2419 (class 0 OID 0)
-- Dependencies: 165
-- Name: T_MEDIA_VALUE_MEV_MEV_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_MEDIA_VALUE_MEV_MEV_ID_seq"', 1, true);


--
-- TOC entry 2420 (class 0 OID 0)
-- Dependencies: 214
-- Name: T_OPTION_OPT_OPT_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_OPTION_OPT_OPT_ID_seq"', 1, false);


--
-- TOC entry 2421 (class 0 OID 0)
-- Dependencies: 203
-- Name: T_ORGANIZATION_FIELD_OFI_OFI_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ORGANIZATION_FIELD_OFI_OFI_ID_seq"', 1, false);


--
-- TOC entry 2422 (class 0 OID 0)
-- Dependencies: 173
-- Name: T_ORGANIZATION_ORG_ORG_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ORGANIZATION_ORG_ORG_ID_seq"', 2, true);


--
-- TOC entry 2423 (class 0 OID 0)
-- Dependencies: 171
-- Name: T_ORGANIZATION_TYPE_OTY_OTY_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_ORGANIZATION_TYPE_OTY_OTY_ID_seq"', 1, false);


--
-- TOC entry 2424 (class 0 OID 0)
-- Dependencies: 169
-- Name: T_PACK_PCK_PCK_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_PACK_PCK_PCK_ID_seq"', 1, false);


--
-- TOC entry 2425 (class 0 OID 0)
-- Dependencies: 140
-- Name: T_PLUGIN_PLG_PLG_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_PLUGIN_PLG_PLG_ID_seq"', 1, false);


--
-- TOC entry 2426 (class 0 OID 0)
-- Dependencies: 190
-- Name: T_PROBE_PRB_PRB_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_PROBE_PRB_PRB_ID_seq"', 1, false);


--
-- TOC entry 2427 (class 0 OID 0)
-- Dependencies: 184
-- Name: T_SEARCH_PARAMETER_SEP_SEP_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SEARCH_PARAMETER_SEP_SEP_ID_seq"', 1, false);


--
-- TOC entry 2428 (class 0 OID 0)
-- Dependencies: 145
-- Name: T_SEARCH_TYPE_STY_STY_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SEARCH_TYPE_STY_STY_ID_seq"', 1, false);


--
-- TOC entry 2429 (class 0 OID 0)
-- Dependencies: 186
-- Name: T_SOURCE_PARAMETER_SRP_SRP_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SOURCE_PARAMETER_SRP_SRP_ID_seq"', 1, false);


--
-- TOC entry 2430 (class 0 OID 0)
-- Dependencies: 198
-- Name: T_SPACE_SPA_SPA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SPACE_SPA_SPA_ID_seq"', 1, false);


--
-- TOC entry 2431 (class 0 OID 0)
-- Dependencies: 194
-- Name: T_SYSLOG_SLO_SLO_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_SYSLOG_SLO_SLO_ID_seq"', 53955, true);


--
-- TOC entry 2432 (class 0 OID 0)
-- Dependencies: 167
-- Name: T_USER_ACTION_ACT_UAC_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_ACTION_ACT_UAC_ID_seq"', 1, false);


--
-- TOC entry 2433 (class 0 OID 0)
-- Dependencies: 216
-- Name: T_USER_FIELD_UFI_UFI_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_FIELD_UFI_UFI_ID_seq"', 1, false);


--
-- TOC entry 2434 (class 0 OID 0)
-- Dependencies: 210
-- Name: T_USER_HISTORICAL_ACTION_UHA_UHA_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_HISTORICAL_ACTION_UHA_UHA_ID_seq"', 1, false);


--
-- TOC entry 2435 (class 0 OID 0)
-- Dependencies: 161
-- Name: T_USER_PROFILE_UPR_UPR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_PROFILE_UPR_UPR_ID_seq"', 1, false);


--
-- TOC entry 2436 (class 0 OID 0)
-- Dependencies: 200
-- Name: T_USER_RIGHT_URI_URI_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_RIGHT_URI_URI_ID_seq"', 1, false);


--
-- TOC entry 2437 (class 0 OID 0)
-- Dependencies: 159
-- Name: T_USER_ROLE_URO_URO_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_ROLE_URO_URO_ID_seq"', 1, false);


--
-- TOC entry 2438 (class 0 OID 0)
-- Dependencies: 163
-- Name: T_USER_USR_USR_ID_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('"T_USER_USR_USR_ID_seq"', 2, true);


--
-- TOC entry 2439 (class 0 OID 0)
-- Dependencies: 221
-- Name: auth_identity_id_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('auth_identity_id_seq', 2, true);


--
-- TOC entry 2440 (class 0 OID 0)
-- Dependencies: 219
-- Name: auth_info_id_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('auth_info_id_seq', 2, true);


--
-- TOC entry 2441 (class 0 OID 0)
-- Dependencies: 223
-- Name: auth_token_id_seq; Type: SEQUENCE SET; Schema: public; Owner: echoes
--

SELECT pg_catalog.setval('auth_token_id_seq', 109, true);


--
-- TOC entry 2352 (class 0 OID 36468)
-- Dependencies: 154 2400
-- Data for Name: T_ALERT_CRITERIA_ACR; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (1, 0, 'lt', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (2, 0, 'le', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (3, 0, 'eq', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (4, 0, 'ne', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (5, 0, 'ge', NULL);
INSERT INTO "T_ALERT_CRITERIA_ACR" ("ACR_ID", version, "ACR_NAME", "ACR_DELETE") VALUES (6, 0, 'gt', NULL);


--
-- TOC entry 2349 (class 0 OID 36423)
-- Dependencies: 149 2400
-- Data for Name: T_INFORMATION_UNIT_TYPE_UTY; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_UNIT_TYPE_UTY" ("IUT_ID", version, "IUT_NAME", "IUT_DELETE") VALUES (0, 0, 'number', NULL);
INSERT INTO "T_INFORMATION_UNIT_TYPE_UTY" ("IUT_ID", version, "IUT_NAME", "IUT_DELETE") VALUES (1, 0, 'text', NULL);


--
-- TOC entry 2394 (class 0 OID 37138)
-- Dependencies: 228 2352 2349 2400
-- Data for Name: TJ_ACR_IUT; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (1, 0);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (2, 0);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (3, 0);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (4, 0);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (5, 0);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (6, 0);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (3, 1);
INSERT INTO "TJ_ACR_IUT" ("T_ALERT_CRITERIA_ACR_ACR_ID", "T_INFORMATION_UNIT_TYPE_UTY_IUT_ID") VALUES (4, 1);


--
-- TOC entry 2345 (class 0 OID 36368)
-- Dependencies: 143 2400
-- Data for Name: T_ADDON_ADO; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (2, 0, 'file', NULL);


--
-- TOC entry 2369 (class 0 OID 36731)
-- Dependencies: 187 2400
-- Data for Name: T_SOURCE_PARAMETER_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (0, 0, 'text', 'path', NULL);


--
-- TOC entry 2395 (class 0 OID 37172)
-- Dependencies: 229 2369 2345 2400
-- Data for Name: TJ_ADO_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (0, 2);


--
-- TOC entry 2361 (class 0 OID 36597)
-- Dependencies: 172 2400
-- Data for Name: T_ORGANIZATION_TYPE_OTY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2360 (class 0 OID 36586)
-- Dependencies: 170 2400
-- Data for Name: T_PACK_PCK; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PACK_PCK" ("PCK_ID", version, "PCK_NAME", "PCK_DELETE") VALUES (0, 0, 'alpha', NULL);


--
-- TOC entry 2362 (class 0 OID 36608)
-- Dependencies: 174 2360 2361 2400
-- Data for Name: T_ORGANIZATION_ORG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (1, 0, '', '', '', 'Saquet', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (2, 0, '', '', '', 'Saquet', NULL, NULL, NULL);
INSERT INTO "T_ORGANIZATION_ORG" ("ORG_ID", version, "ORG_ADR", "ORG_CITY", "ORG_CP", "ORG_NAME", "ORG_DELETE", "ORG_PCK_PCK_ID", "ORG_OTY_OTY_ID") VALUES (3, 0, '5 pl F.Poulenc', 'Montigny', '78180', 'Cheyennes', NULL, 0, NULL);


--
-- TOC entry 2371 (class 0 OID 36763)
-- Dependencies: 191 2362 2400
-- Data for Name: T_PROBE_PRB; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PROBE_PRB" ("PRB_ID", version, "PRB_CERT", "PRB_NAME", "PRB_DELETE", "PRB_ORG_ORG_ID") VALUES (6585, 0, 'temp', 'rhi-laptop-ea-probe', NULL, 3);


--
-- TOC entry 2372 (class 0 OID 36779)
-- Dependencies: 193 2371 2400
-- Data for Name: T_ASSET_AST; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ASSET_AST" ("AST_ID", version, "AST_NAME", "AST_DELETE", "AST_IS_HOST", "AST_PRB_PRB_ID") VALUES (1, 0, 'rhi-laptop', NULL, true, 6585);


--
-- TOC entry 2344 (class 0 OID 36357)
-- Dependencies: 141 2400
-- Data for Name: T_PLUGIN_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (1, 0, 'Debian 6.0 - System - Test', 'System', NULL);


--
-- TOC entry 2399 (class 0 OID 37240)
-- Dependencies: 233 2372 2344 2400
-- Data for Name: TJ_AST_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_AST_PLG" ("T_ASSET_AST_AST_ID", "T_PLUGIN_PLG_PLG_ID") VALUES (1, 1);


--
-- TOC entry 2350 (class 0 OID 36434)
-- Dependencies: 151 2349 2400
-- Data for Name: T_INFORMATION_UNIT_UNT; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (1, 0, 'Packets', 'Pkts', NULL, 0);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (2, 0, 'Bytes', 'Bytes', NULL, 0);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (0, 0, 'Kilo Bytes', 'Kb', NULL, 0);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (3, 0, 'name', 'name', NULL, 1);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (4, 0, 'load', 'load', NULL, 0);
INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (5, 0, 'Time in USER_Hz', 'time in USER_Hz', NULL, 0);


--
-- TOC entry 2347 (class 0 OID 36394)
-- Dependencies: 146 2400
-- Data for Name: T_SEARCH_TYPE_STY; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_TYPE_STY" ("STY_ID", version, "STY_NAME", "STY_DELETE") VALUES (0, 0, 'regex', NULL);


--
-- TOC entry 2346 (class 0 OID 36377)
-- Dependencies: 144 2344 2345 2400
-- Data for Name: T_SOURCE_SRC; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 1, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 2, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 3, 1, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 4, 1, 2);


--
-- TOC entry 2348 (class 0 OID 36403)
-- Dependencies: 147 2346 2347 2400
-- Data for Name: T_SEARCH_SEA; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_POS_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 1, 1, 1, 0, 0);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_POS_KEY_VALUE") VALUES (0, 'default', NULL, false, 9, 1, 2, 1, 0, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_POS_KEY_VALUE") VALUES (0, 'default', NULL, false, 3, 1, 3, 1, 0, 0);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_POS_KEY_VALUE") VALUES (0, 'default', NULL, false, 5, 1, 4, 1, 0, 1);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_POS_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 2, 1, 1, 0, 0);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_POS_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 3, 1, 1, 0, 0);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_POS_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 4, 1, 1, 0, 0);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_POS_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 5, 1, 1, 0, 0);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_POS_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 6, 1, 1, 0, 0);


--
-- TOC entry 2351 (class 0 OID 36448)
-- Dependencies: 152 2348 2350 2400
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
-- TOC entry 2353 (class 0 OID 36479)
-- Dependencies: 156 2351 2352 2400
-- Data for Name: T_ALERT_VALUE_AVA; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ALERT_VALUE_AVA" ("AVA_ID", version, "AVA_VALUE", "AVA_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "AVA_ACR_ACR_ID", "AVA_KEY_VALUE") VALUES (0, 0, '0.5', NULL, 1, 3, 1, 1, 5, NULL);
INSERT INTO "T_ALERT_VALUE_AVA" ("AVA_ID", version, "AVA_VALUE", "AVA_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "AVA_ACR_ACR_ID", "AVA_KEY_VALUE") VALUES (1, 0, '4762924', NULL, 2, 1, 1, 1, 1, NULL);


--
-- TOC entry 2363 (class 0 OID 36629)
-- Dependencies: 176 2353 2400
-- Data for Name: T_ALERT_SEQUENCE_ASE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2364 (class 0 OID 36647)
-- Dependencies: 178 2400
-- Data for Name: T_ENGINE_ENG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ENGINE_ENG" ("ENG_ID", version, "ENG_FQDN", "ENG_STATE", "ENG_DELETE", "ENG_KEEP_ALIVE", "ENG_NB_THREAD") VALUES (0, 0, 'rhi-laptop.echoes-tech.com', '0', NULL, NULL, 100);


--
-- TOC entry 2365 (class 0 OID 36658)
-- Dependencies: 180 2353 2363 2364 2400
-- Data for Name: T_ALERT_ALE; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ALERT_ALE" ("ALE_ID", version, "ALE_NAME", "ALE_CREA_DATE", "ALE_DELETE", "ALE_LAST_ATTEMPT", "ALE_THREAD_SLEEP", "ALE_AVA_AVA_ID", "ASE_FIRST_ID_ASE_ID", "ALE_ENG_ENG_ID") VALUES (0, 163, 'surcharge système', '2012-09-08 23:48:24', NULL, '2012-09-10 19:37:37.230017', 0, 0, NULL, 0);
INSERT INTO "T_ALERT_ALE" ("ALE_ID", version, "ALE_NAME", "ALE_CREA_DATE", "ALE_DELETE", "ALE_LAST_ATTEMPT", "ALE_THREAD_SLEEP", "ALE_AVA_AVA_ID", "ASE_FIRST_ID_ASE_ID", "ALE_ENG_ENG_ID") VALUES (1, 68, 'occupation mémoire', '2012-09-08 23:48:24', NULL, '2012-09-10 19:37:37.232249', 0, 1, NULL, 0);


--
-- TOC entry 2354 (class 0 OID 36500)
-- Dependencies: 158 2400
-- Data for Name: T_MEDIA_MED; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_MEDIA_MED" ("MED_ID", version, "MED_NAME", "MED_DELETE") VALUES (0, 0, 'sms', NULL);
INSERT INTO "T_MEDIA_MED" ("MED_ID", version, "MED_NAME", "MED_DELETE") VALUES (1, 0, 'mail', NULL);


--
-- TOC entry 2356 (class 0 OID 36522)
-- Dependencies: 162 2400
-- Data for Name: T_USER_PROFILE_UPR; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2355 (class 0 OID 36511)
-- Dependencies: 160 2400
-- Data for Name: T_USER_ROLE_URO; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2357 (class 0 OID 36533)
-- Dependencies: 164 2355 2356 2400
-- Data for Name: T_USER_USR; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "USR_UPR_UPR_ID") VALUES (0, 0, 'Romain', 'Hinfray', 'neorom@gmail.com', 'toto', NULL, NULL, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "USR_UPR_UPR_ID") VALUES (1, 0, 'Thomas', 'Saquet', 'tsaquet@gmail.com', '', NULL, NULL, NULL);
INSERT INTO "T_USER_USR" ("USR_ID", version, "USR_FIRST_NAME", "USR_LAST_NAME", "USR_MAIL", "USR_PWD", "USR_DELETE", "USR_URO_URO_ID", "USR_UPR_UPR_ID") VALUES (2, 0, 'Thomas', 'Saquet', 'tsaquet@yahoo.fr', '', NULL, NULL, NULL);


--
-- TOC entry 2358 (class 0 OID 36554)
-- Dependencies: 166 2354 2357 2400
-- Data for Name: T_MEDIA_VALUE_MEV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_MEDIA_VALUE_MEV" ("MEV_ID", version, "MEV_VALUE", "MEV_DELETE", "MEV_NOTIF_END_OF_ALERT", "MEV_SNOOZE", "MEV_MED_MED_ID", "MEV_USR_USR_ID", "MEV_LAST_SEND") VALUES (1, 0, 'tsaquet@gmail.com', NULL, false, 60, 1, 1, NULL);
INSERT INTO "T_MEDIA_VALUE_MEV" ("MEV_ID", version, "MEV_VALUE", "MEV_DELETE", "MEV_NOTIF_END_OF_ALERT", "MEV_SNOOZE", "MEV_MED_MED_ID", "MEV_USR_USR_ID", "MEV_LAST_SEND") VALUES (2, 11, 'neorom@gmail.com', NULL, false, 30, 1, 0, '2012-09-10 19:37:51.555884');
INSERT INTO "T_MEDIA_VALUE_MEV" ("MEV_ID", version, "MEV_VALUE", "MEV_DELETE", "MEV_NOTIF_END_OF_ALERT", "MEV_SNOOZE", "MEV_MED_MED_ID", "MEV_USR_USR_ID", "MEV_LAST_SEND") VALUES (0, 28, '+33607874128', NULL, false, 10, 0, 0, '2012-09-10 19:37:51.75543');


--
-- TOC entry 2391 (class 0 OID 37087)
-- Dependencies: 225 2358 2365 2400
-- Data for Name: TJ_MEV_ALE; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_MEV_ALE" ("T_MEDIA_VALUE_MEV_MEV_ID", "T_ALERT_ALE_ALE_ID") VALUES (0, 0);
INSERT INTO "TJ_MEV_ALE" ("T_MEDIA_VALUE_MEV_MEV_ID", "T_ALERT_ALE_ALE_ID") VALUES (0, 1);
INSERT INTO "TJ_MEV_ALE" ("T_MEDIA_VALUE_MEV_MEV_ID", "T_ALERT_ALE_ALE_ID") VALUES (2, 0);


--
-- TOC entry 2378 (class 0 OID 36879)
-- Dependencies: 204 2400
-- Data for Name: T_ORGANIZATION_FIELD_OFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2396 (class 0 OID 37189)
-- Dependencies: 230 2361 2378 2400
-- Data for Name: TJ_OFI_OTY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2385 (class 0 OID 37004)
-- Dependencies: 215 2400
-- Data for Name: T_OPTION_OPT; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2397 (class 0 OID 37206)
-- Dependencies: 231 2360 2385 2400
-- Data for Name: TJ_PCK_OPT; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2368 (class 0 OID 36720)
-- Dependencies: 185 2400
-- Data for Name: T_SEARCH_PARAMETER_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_PARAMETER_SEP" ("SEP_ID", version, "SEP_FORMAT", "SEP_NAME", "SEP_DELETE") VALUES (0, 0, 'text', 'regex', NULL);


--
-- TOC entry 2392 (class 0 OID 37104)
-- Dependencies: 226 2347 2368 2400
-- Data for Name: TJ_STY_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_STY_SEP" ("T_SEARCH_TYPE_STY_STY_ID", "T_SEARCH_PARAMETER_SEP_SEP_ID") VALUES (0, 0);


--
-- TOC entry 2393 (class 0 OID 37121)
-- Dependencies: 227 2362 2357 2400
-- Data for Name: TJ_USR_ORG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (2, 2);
INSERT INTO "TJ_USR_ORG" ("T_ORGANIZATION_ORG_ORG_ID", "T_USER_USR_USR_ID") VALUES (3, 0);


--
-- TOC entry 2386 (class 0 OID 37015)
-- Dependencies: 217 2400
-- Data for Name: T_USER_FIELD_UFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2398 (class 0 OID 37223)
-- Dependencies: 232 2357 2386 2400
-- Data for Name: TJ_USR_UFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2375 (class 0 OID 36837)
-- Dependencies: 199 2400
-- Data for Name: T_SPACE_SPA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2376 (class 0 OID 36848)
-- Dependencies: 201 2400
-- Data for Name: T_USER_RIGHT_URI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2377 (class 0 OID 36857)
-- Dependencies: 202 2375 2356 2376 2400
-- Data for Name: T_ACCESS_CONTROL_LIST_ACL; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2370 (class 0 OID 36742)
-- Dependencies: 189 2365 2357 2400
-- Data for Name: T_ALERT_ACKNOWLEDGE_ACK; Type: TABLE DATA; Schema: public; Owner: echoes
--





--
-- TOC entry 2380 (class 0 OID 36908)
-- Dependencies: 207 2366 2400
-- Data for Name: T_ALERT_TRACKING_EVENT_ATE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2373 (class 0 OID 36795)
-- Dependencies: 195 2371 2400
-- Data for Name: T_SYSLOG_SLO; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2384 (class 0 OID 36978)
-- Dependencies: 213 2372 2373 2351 2400
-- Data for Name: T_INFORMATION_HISTORICAL_VALUE_IHV; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2374 (class 0 OID 36811)
-- Dependencies: 197 2372 2373 2351 2400
-- Data for Name: T_INFORMATION_VALUE_IVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2379 (class 0 OID 36888)
-- Dependencies: 205 2378 2362 2400
-- Data for Name: T_ORGANIZATION_VALUE_OVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2381 (class 0 OID 36922)
-- Dependencies: 208 2348 2368 2400
-- Data for Name: T_SEARCH_PARAMETER_VALUE_SEV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^MemTotal:\\s+([0-9]+)\\skB', NULL, 1, 1, 1, 0);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^MemFree:\\s+([0-9]+)\\skB', NULL, 2, 1, 1, 0);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^Buffers:\\s+([0-9]+)\\skB', NULL, 3, 1, 1, 0);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^Cached:\\s+([0-9]+)\\skB', NULL, 4, 1, 1, 0);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^SwapTotal:\\s+([0-9]+)\\skB', NULL, 5, 1, 1, 0);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^SwapFree:\\s+([0-9]+)\\skB', NULL, 6, 1, 1, 0);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^\\s*(\\w+):\\s*([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+\\s+[0-9]+', NULL, 1, 2, 1, 0);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^([0-9]+\\.[0-9]+)\\s([0-9]+\\.[0-9]+)\\s([0-9]+\\.[0-9]+)', NULL, 1, 3, 1, 0);
INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, '^(cpu[0-9]*)\\s+([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s([0-9]+)\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+\\s[0-9]+', NULL, 1, 4, 1, 0);


--
-- TOC entry 2382 (class 0 OID 36940)
-- Dependencies: 209 2369 2346 2400
-- Data for Name: T_SOURCE_PARAMETER_VALUE_SPV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/meminfo', NULL, 0, 1, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/net/dev', NULL, 0, 2, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/loadavg', NULL, 0, 3, 1);
INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/stat', NULL, 0, 4, 1);


--
-- TOC entry 2359 (class 0 OID 36575)
-- Dependencies: 168 2400
-- Data for Name: T_USER_ACTION_ACT; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2367 (class 0 OID 36703)
-- Dependencies: 183 2357 2357 2400
-- Data for Name: T_USER_HIERARCHY_UHI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2383 (class 0 OID 36960)
-- Dependencies: 211 2357 2359 2400
-- Data for Name: T_USER_HISTORICAL_ACTION_UHA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2387 (class 0 OID 37024)
-- Dependencies: 218 2357 2386 2400
-- Data for Name: T_USER_VALUE_UVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2388 (class 0 OID 37044)
-- Dependencies: 220 2357 2400
-- Data for Name: auth_info; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (2, 3, 2, '$2y$07$REnsXlnhLFDraVjSakG2YePQCjCXiNTTg8/AdVnAPgQ8eH3tHbXdW', 'bcrypt', 'Ljnfzc4qmqyTrb8j', 1, 0, NULL, 'tsaquet@yahoo.fr', '', '', NULL, 1);
INSERT INTO auth_info (id, version, "user_USR_ID", password_hash, password_method, password_salt, status, failed_login_attempts, last_login_attempt, email, unverified_email, email_token, email_token_expires, email_token_role) VALUES (1, 126, 1, '$2y$07$bSiuLx/HMDjDKSfYcjG3Q.7UR0uJhw.PL2MpV4U4RGN9j2U.Oc.7O', 'bcrypt', 'uI070I8YE1HZzR9H', 1, 0, '2012-09-10 20:39:41.090106', '', 'tsaquet@gmail.com', 't5meFuBULVHDqIUBYwtQNg==', '2012-09-12 16:30:23.745956', 0);


--
-- TOC entry 2389 (class 0 OID 37060)
-- Dependencies: 222 2388 2400
-- Data for Name: auth_identity; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (1, 0, 1, 'loginname', 'tsaquet@gmail.com');
INSERT INTO auth_identity (id, version, auth_info_id, provider, identity) VALUES (2, 0, 2, 'loginname', 'tsaquet@yahoo.fr');


--
-- TOC entry 2390 (class 0 OID 37076)
-- Dependencies: 224 2388 2400
-- Data for Name: auth_token; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (58, 0, 1, 'PmGr0xDC1PxfW46XzdE.ag==', '2012-09-24 11:00:24.470409');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (59, 0, 1, 'pA7884Zd9MMiurXis.bOGQ==', '2012-09-24 11:10:05.130837');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (88, 0, 1, 'r4MH/AkktttUbbmpnSnBvg==', '2012-09-24 14:38:55.416464');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (103, 0, 1, 'ezuo8fwsgyFCcscRCLktgA==', '2012-09-24 20:35:05.666006');
INSERT INTO auth_token (id, version, auth_info_id, value, expires) VALUES (109, 0, 1, 't5mn795dHjUYHtKYc1unBQ==', '2012-09-24 21:19:32.617721');


-- Completed on 2012-09-11 01:06:03 CEST

--
-- PostgreSQL database dump complete
--


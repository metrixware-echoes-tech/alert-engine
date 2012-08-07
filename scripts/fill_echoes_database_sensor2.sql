--
-- PostgreSQL database dump
--

-- Dumped from database version 8.4.12
-- Dumped by pg_dump version 9.1.4
-- Started on 2012-08-07 15:04:51 CEST

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

SET search_path = public, pg_catalog;


--
-- TOC entry 2347 (class 0 OID 27285)
-- Dependencies: 149
-- Data for Name: T_ADDON_ADO; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (2, 1, 'file', NULL);
INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (3, 1, 'log', NULL);


--
-- TOC entry 2368 (class 0 OID 27598)
-- Dependencies: 187
-- Data for Name: T_SOURCE_PARAMETER_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2394 (class 0 OID 28027)
-- Dependencies: 229 2347 2368
-- Data for Name: TJ_ADO_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2362 (class 0 OID 27508)
-- Dependencies: 176
-- Data for Name: T_ORGANIZATION_TYPE_OTY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2361 (class 0 OID 27497)
-- Dependencies: 174
-- Data for Name: T_PACK_PCK; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2363 (class 0 OID 27519)
-- Dependencies: 178 2362 2361
-- Data for Name: T_ORGANIZATION_ORG; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2370 (class 0 OID 27630)
-- Dependencies: 191 2363
-- Data for Name: T_PROBE_PRB; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PROBE_PRB" ("PRB_ID", version, "PRB_KEY", "PRB_NAME", "PRB_DELETE", "PRB_ORG_ORG_ID") VALUES (6585, 1, 'the pass', 'helios', NULL, NULL);


--
-- TOC entry 2371 (class 0 OID 27646)
-- Dependencies: 193 2370
-- Data for Name: T_ASSET_AST; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ASSET_AST" ("AST_ID", version, "AST_NAME", "AST_DELETE", "AST_IS_HOST", "AST_PRB_PRB_ID") VALUES (1, 1, 'helios', NULL, true, 6585);


--
-- TOC entry 2346 (class 0 OID 27274)
-- Dependencies: 147
-- Data for Name: T_PLUGIN_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (2, 1, 'test', 'Helios_Debian6.0-Syslog-Test', NULL);
INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (1, 1, 'memoire vive totale', 'memoire vive totale du système', NULL);


--
-- TOC entry 2398 (class 0 OID 28095)
-- Dependencies: 233 2346 2371
-- Data for Name: TJ_AST_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_AST_PLG" ("T_ASSET_AST_AST_ID", "T_PLUGIN_PLG_PLG_ID") VALUES (1, 2);
INSERT INTO "TJ_AST_PLG" ("T_ASSET_AST_AST_ID", "T_PLUGIN_PLG_PLG_ID") VALUES (1, 1);


--
-- TOC entry 2344 (class 0 OID 27247)
-- Dependencies: 143
-- Data for Name: T_ALERT_TYPE_ATY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2393 (class 0 OID 28010)
-- Dependencies: 228 2344 2364
-- Data for Name: TJ_ATY_ACR; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2377 (class 0 OID 27746)
-- Dependencies: 204
-- Data for Name: T_ORGANIZATION_FIELD_OFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2395 (class 0 OID 28044)
-- Dependencies: 230 2377 2362
-- Data for Name: TJ_OFI_OTY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2384 (class 0 OID 27876)
-- Dependencies: 215
-- Data for Name: T_OPTION_OPT; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2396 (class 0 OID 28061)
-- Dependencies: 231 2384 2361
-- Data for Name: TJ_PCK_OPT; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2367 (class 0 OID 27587)
-- Dependencies: 185
-- Data for Name: T_SEARCH_PARAMETER_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2349 (class 0 OID 27311)
-- Dependencies: 152
-- Data for Name: T_SEARCH_TYPE_STY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2391 (class 0 OID 27976)
-- Dependencies: 226 2367 2349
-- Data for Name: TJ_STY_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2357 (class 0 OID 27433)
-- Dependencies: 166
-- Data for Name: T_USER_PROFILE_UPR; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2356 (class 0 OID 27422)
-- Dependencies: 164
-- Data for Name: T_USER_ROLE_URO; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2358 (class 0 OID 27444)
-- Dependencies: 168 2357 2356
-- Data for Name: T_USER_USR; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2392 (class 0 OID 27993)
-- Dependencies: 227 2358 2363
-- Data for Name: TJ_USR_ORG; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2385 (class 0 OID 27887)
-- Dependencies: 217
-- Data for Name: T_USER_FIELD_UFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2397 (class 0 OID 28078)
-- Dependencies: 232 2385 2358
-- Data for Name: TJ_USR_UFI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2374 (class 0 OID 27704)
-- Dependencies: 199
-- Data for Name: T_SPACE_SPA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2375 (class 0 OID 27715)
-- Dependencies: 201
-- Data for Name: T_USER_RIGHT_URI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2376 (class 0 OID 27724)
-- Dependencies: 202 2375 2357 2374
-- Data for Name: T_ACCESS_CONTROL_LIST_ACL; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2345 (class 0 OID 27258)
-- Dependencies: 145 2344
-- Data for Name: T_ALERT_ALE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2369 (class 0 OID 27609)
-- Dependencies: 189 2358 2345
-- Data for Name: T_ALERT_ACKNOWLEDGE_ACK; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2355 (class 0 OID 27411)
-- Dependencies: 162
-- Data for Name: T_MEDIA_MED; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2359 (class 0 OID 27465)
-- Dependencies: 170 2358 2355
-- Data for Name: T_MEDIA_VALUE_MEV; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2365 (class 0 OID 27551)
-- Dependencies: 182 2345 2359
-- Data for Name: T_ALERT_TRACKING_ATR; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2379 (class 0 OID 27775)
-- Dependencies: 207 2365
-- Data for Name: T_ALERT_TRACKING_EVENT_ATE; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2351 (class 0 OID 27340)
-- Dependencies: 155
-- Data for Name: T_INFORMATION_UNIT_TYPE_UTY; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2352 (class 0 OID 27351)
-- Dependencies: 157 2351
-- Data for Name: T_INFORMATION_UNIT_UNT; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2348 (class 0 OID 27294)
-- Dependencies: 150 2347 2346
-- Data for Name: T_SOURCE_SRC; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (1, NULL, 3, 2, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (1, NULL, 2, 2, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (1, NULL, 1, 1, 2);


--
-- TOC entry 2350 (class 0 OID 27320)
-- Dependencies: 153 2349 2348
-- Data for Name: T_SEARCH_SEA; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (1, '60', NULL, true, 1, 1, 3, 2, NULL);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (1, '60', NULL, true, 1, 1, 2, 2, NULL);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (1, '60', NULL, true, 1, 1, 1, 1, NULL);


--
-- TOC entry 2353 (class 0 OID 27365)
-- Dependencies: 158 2352 2350
-- Data for Name: T_INFORMATION_INF; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_UNT_INU_ID") VALUES (1, 'clef1', NULL, 1, 3, 2, 0, NULL);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_UNT_INU_ID") VALUES (1, 'clef2', NULL, 1, 2, 2, 0, NULL);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_UNT_INU_ID") VALUES (1, 'memoire totale', NULL, 1, 1, 1, 0, NULL);


--
-- TOC entry 2354 (class 0 OID 27385)
-- Dependencies: 160 2353 2343 2345
-- Data for Name: T_ALERT_VALUE_AVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2372 (class 0 OID 27662)
-- Dependencies: 195 2370
-- Data for Name: T_SYSLOG_SLO; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SYSLOG_SLO" ("SLO_ID", version, "SLO_APP_NAME", "SLO_HOSTNAME", "SLO_MSG_ID", "SLO_SD", "SLO_DELETE", "SLO_RCPT_DATE", "SLO_SENT_DATE", "SLO_PRI", "SLO_PROC_ID", "SLO_STATE", "SLO_VERSION", "SLO_PRB_PRB_ID") VALUES (19, 2, 'echoes-alert-probe', 'rhi-laptop.ptf.echoes-tech.com', 'ID2', '[prop@40311 ver=1 probe=6585][res1@40311 offset=2 2-1-2-1-0="b3Aga2VybmVsOg=="]', NULL, '2012-08-07 15:02:32', '2012-08-07 15:02:32', 118, 16149, 2, NULL, NULL);
INSERT INTO "T_SYSLOG_SLO" ("SLO_ID", version, "SLO_APP_NAME", "SLO_HOSTNAME", "SLO_MSG_ID", "SLO_SD", "SLO_DELETE", "SLO_RCPT_DATE", "SLO_SENT_DATE", "SLO_PRI", "SLO_PROC_ID", "SLO_STATE", "SLO_VERSION", "SLO_PRB_PRB_ID") VALUES (18, 2, 'echoes-alert-probe', 'rhi-laptop.ptf.echoes-tech.com', 'ID1', '[prop@40311 ver=1 probe=6585][res1@40311 offset=2 2-1-3-1-0="YiBjZHJvbTpbVQ=="]', NULL, '2012-08-07 15:02:32', '2012-08-07 15:02:32', 118, 16149, 2, NULL, NULL);


--
-- TOC entry 2383 (class 0 OID 27850)
-- Dependencies: 213 2353 2372 2371
-- Data for Name: T_INFORMATION_HISTORICAL_VALUE_IHV; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2373 (class 0 OID 27678)
-- Dependencies: 197 2353 2372 2371
-- Data for Name: T_INFORMATION_VALUE_IVA; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_VALUE_IVA" ("IVA_ID", version, "IVA_VALUE", "IVA_CREA_DATE", "IVA_DELETE", "IVA_AST_AST_ID", "IVA_SLO_SLO_ID", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM") VALUES (27, 0, 'b cdrom:[U', '2012-08-07 15:02:34', NULL, 1, 18, 1, 3, 2, 0);
INSERT INTO "T_INFORMATION_VALUE_IVA" ("IVA_ID", version, "IVA_VALUE", "IVA_CREA_DATE", "IVA_DELETE", "IVA_AST_AST_ID", "IVA_SLO_SLO_ID", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM") VALUES (28, 0, 'op kernel:', '2012-08-07 15:02:34', NULL, 1, 19, 1, 2, 2, 0);


--
-- TOC entry 2378 (class 0 OID 27755)
-- Dependencies: 205 2363 2377
-- Data for Name: T_ORGANIZATION_VALUE_OVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2380 (class 0 OID 27789)
-- Dependencies: 208 2367 2350
-- Data for Name: T_SEARCH_PARAMETER_VALUE_SEV; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2381 (class 0 OID 27807)
-- Dependencies: 209 2368 2348 2368
-- Data for Name: T_SOURCE_PARAMETER_VALUE_SPV; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2360 (class 0 OID 27486)
-- Dependencies: 172
-- Data for Name: T_USER_ACTION_ACT; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2366 (class 0 OID 27570)
-- Dependencies: 183 2358 2358
-- Data for Name: T_USER_HIERARCHY_UHI; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2382 (class 0 OID 27832)
-- Dependencies: 211 2360 2358
-- Data for Name: T_USER_HISTORICAL_ACTION_UHA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2386 (class 0 OID 27896)
-- Dependencies: 218 2385 2358
-- Data for Name: T_USER_VALUE_UVA; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2387 (class 0 OID 27916)
-- Dependencies: 220 2358
-- Data for Name: auth_info; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2388 (class 0 OID 27932)
-- Dependencies: 222 2387
-- Data for Name: auth_identity; Type: TABLE DATA; Schema: public; Owner: echoes
--



--
-- TOC entry 2389 (class 0 OID 27948)
-- Dependencies: 224 2387
-- Data for Name: auth_token; Type: TABLE DATA; Schema: public; Owner: echoes
--



-- Completed on 2012-08-07 15:04:52 CEST

--
-- PostgreSQL database dump complete
--


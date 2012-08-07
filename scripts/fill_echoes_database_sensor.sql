--
-- PostgreSQL database dump
--

-- Dumped from database version 9.1.4
-- Dumped by pg_dump version 9.1.4
-- Started on 2012-08-04 17:31:06 CEST

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

SET search_path = public, pg_catalog;



--
-- TOC entry 2213 (class 0 OID 24164)
-- Dependencies: 211
-- Data for Name: T_PROBE_PRB; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PROBE_PRB" ("PRB_ID", version, "PRB_KEY", "PRB_NAME", "PRB_DELETE", "PRB_ORG_ORG_ID") VALUES (6585, 1, 'the pass', 'helios', NULL, NULL);


--
-- TOC entry 2214 (class 0 OID 24180)
-- Dependencies: 213 2213
-- Data for Name: T_ASSET_AST; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ASSET_AST" ("AST_ID", version, "AST_NAME", "AST_DELETE", "AST_IS_HOST", "AST_PRB_PRB_ID") VALUES (1, 1, 'helios', NULL, true, 6585);


--
-- TOC entry 2208 (class 0 OID 23931)
-- Dependencies: 183
-- Data for Name: T_PLUGIN_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (2, 1, 'test', 'Helios_Debian6.0-Syslog-Test', NULL);


--
-- TOC entry 2216 (class 0 OID 24624)
-- Dependencies: 253 2214 2208
-- Data for Name: TJ_AST_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_AST_PLG" ("T_ASSET_AST_AST_ID", "T_PLUGIN_PLG_PLG_ID") VALUES (1, 2);


--
-- TOC entry 2209 (class 0 OID 23942)
-- Dependencies: 185
-- Data for Name: T_ADDON_ADO; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (2, 1, 'file', NULL);
INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (3, 1, 'log', NULL);


--
-- TOC entry 2210 (class 0 OID 23951)
-- Dependencies: 186 2208 2209
-- Data for Name: T_SOURCE_SRC; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (1, NULL, 3, 2, 2);
INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (1, NULL, 2, 2, 2);


--
-- TOC entry 2211 (class 0 OID 23966)
-- Dependencies: 187 2210
-- Data for Name: T_SEARCH_SEA; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (1, '60', NULL, true, 1, 1, 3, 2, NULL);
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID") VALUES (1, '60', NULL, true, 1, 1, 2, 2, NULL);


--
-- TOC entry 2212 (class 0 OID 24011)
-- Dependencies: 192 2211
-- Data for Name: T_INFORMATION_INF; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_UNT_INU_ID") VALUES (1, 'clef1', NULL, 1, 3, 2, '0', NULL);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_UNT_INU_ID") VALUES (1, 'clef2', NULL, 1, 2, 2, '0', NULL);


--
-- TOC entry 2215 (class 0 OID 24196)
-- Dependencies: 215 2213
-- Data for Name: T_SYSLOG_SLO; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SYSLOG_SLO" ("SLO_ID", version, "SLO_APP_NAME", "SLO_HOSTNAME", "SLO_SD", "SLO_DELETE", "SLO_RCPT_DATE", "SLO_SENT_DATE", "SLO_PRI", "SLO_MSG_ID", "SLO_PROC_ID", "SLO_STATE", "SLO_VERSION", "SLO_PRB_PRB_ID") VALUES (1, 1, 'system', 'helios.gayuxweb.fr', '[prop@5875 ver=1 probe=6585][res1@5875 offset=2 2-1-3-1-0="bSB0aGUgVWJ1bg=="]', NULL, NULL, '2012-08-04 11:30:52', 118, 'ID1', 16834, 0, NULL, NULL);
INSERT INTO "T_SYSLOG_SLO" ("SLO_ID", version, "SLO_APP_NAME", "SLO_HOSTNAME", "SLO_SD", "SLO_DELETE", "SLO_RCPT_DATE", "SLO_SENT_DATE", "SLO_PRI", "SLO_MSG_ID", "SLO_PROC_ID", "SLO_STATE", "SLO_VERSION", "SLO_PRB_PRB_ID") VALUES (2, 1, 'system', 'helios.gayuxweb.fr', '[prop@5875 ver=1 probe=6585][res1@5875 offset=2 2-1-2-1-0="b3Aga2VybmVsOg=="]', NULL, NULL, '2012-08-04 11:30:52', 118, 'ID3', 16834, 0, NULL, NULL);


-- Completed on 2012-08-04 17:31:06 CEST

--
-- PostgreSQL database dump complete
--


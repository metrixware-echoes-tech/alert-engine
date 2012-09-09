--
-- TOC entry 2359 (class 0 OID 34605)
-- Dependencies: 149 2411
-- Data for Name: T_INFORMATION_UNIT_TYPE_UTY; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_UNIT_TYPE_UTY" ("IUT_ID", version, "IUT_NAME", "IUT_DELETE") VALUES (0, 0, 'number', NULL);


--
-- TOC entry 2360 (class 0 OID 34616)
-- Dependencies: 151 2359 2411
-- Data for Name: T_INFORMATION_UNIT_UNT; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_UNIT_UNT" ("INU_ID", version, "INU_LONG_NAME", "INU_NAME", "INU_DELETE", "INU_IUT_IUT_ID") VALUES (0, 0, 'Mega Octets', 'Mo', NULL, 0);


--
-- TOC entry 2355 (class 0 OID 34550)
-- Dependencies: 143 2411
-- Data for Name: T_ADDON_ADO; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ADDON_ADO" ("ADO_ID", version, "ADO_NAME", "ADO_DELETE") VALUES (2, 0, 'File', NULL);


--
-- TOC entry 2379 (class 0 OID 34913)
-- Dependencies: 187 2411
-- Data for Name: T_SOURCE_PARAMETER_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_PARAMETER_SRP" ("SRP_ID", version, "SRP_FORMAT", "SRP_NAME", "SRP_DELETE") VALUES (0, 0, 'text', 'path', NULL);


--
-- TOC entry 2406 (class 0 OID 35359)
-- Dependencies: 230 2355 2379 2411
-- Data for Name: TJ_ADO_SRP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_ADO_SRP" ("T_SOURCE_PARAMETER_SRP_SRP_ID", "T_ADDON_ADO_ADO_ID") VALUES (0, 2);


--
-- TOC entry 2381 (class 0 OID 34945)
-- Dependencies: 191 2372 2411
-- Data for Name: T_PROBE_PRB; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PROBE_PRB" ("PRB_ID", version, "PRB_CERT", "PRB_NAME", "PRB_DELETE", "PRB_ORG_ORG_ID") VALUES (6585, 0, 'temp', 'rhi-laptop-ea-probe', NULL, NULL);


--
-- TOC entry 2382 (class 0 OID 34961)
-- Dependencies: 193 2381 2411
-- Data for Name: T_ASSET_AST; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_ASSET_AST" ("AST_ID", version, "AST_NAME", "AST_DELETE", "AST_IS_HOST", "AST_PRB_PRB_ID") VALUES (1, 0, 'rhi-laptop', NULL, true, 6585);


--
-- TOC entry 2354 (class 0 OID 34539)
-- Dependencies: 141 2411
-- Data for Name: T_PLUGIN_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_PLUGIN_PLG" ("PLG_ID", version, "PLG_DESC", "PLG_NAME", "PLG_DELETE") VALUES (1, 0, 'Debian 6.0 - System - Test', 'Debian 6.0 - System - Test', NULL);


--
-- TOC entry 2410 (class 0 OID 35427)
-- Dependencies: 234 2354 2382 2411
-- Data for Name: TJ_AST_PLG; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_AST_PLG" ("T_ASSET_AST_AST_ID", "T_PLUGIN_PLG_PLG_ID") VALUES (1, 1);


--
-- TOC entry 2357 (class 0 OID 34576)
-- Dependencies: 146 2411
-- Data for Name: T_SEARCH_TYPE_STY; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_TYPE_STY" ("STY_ID", version, "STY_NAME", "STY_DELETE") VALUES (0, 0, 'Regex', NULL);


--
-- TOC entry 2356 (class 0 OID 34559)
-- Dependencies: 144 2355 2354 2411
-- Data for Name: T_SOURCE_SRC; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_SRC" (version, "SRC_DELETE", "SRC_ID", "PLG_ID_PLG_ID", "SRC_ADO_ADO_ID") VALUES (0, NULL, 1, 1, 2);


--
-- TOC entry 2358 (class 0 OID 34585)
-- Dependencies: 147 2357 2356 2411
-- Data for Name: T_SEARCH_SEA; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_LOT_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 1, 1, 1, NULL, '0');
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_LOT_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 2, 1, 1, NULL, '0');
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_LOT_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 3, 1, 1, NULL, '0');
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_LOT_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 4, 1, 1, NULL, '0');
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_LOT_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 5, 1, 1, NULL, '0');
INSERT INTO "T_SEARCH_SEA" (version, "SEA_PERIOD", "SEA_DELETE", "SEA_IS_STATIC", "SEA_NB_VALUE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEA_STY_STY_ID", "SEA_LOT_KEY_VALUE") VALUES (0, 'default', NULL, false, 1, 6, 1, 1, NULL, '0');
--
-- TOC entry 2361 (class 0 OID 34630)
-- Dependencies: 152 2360 2358 2411
-- Data for Name: T_INFORMATION_INF; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Total Memory', NULL, 1, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory cree', NULL, 2, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Buffers', NULL, 3, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory cached', NULL, 4, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory Swap size', NULL, 5, 1, 1, 1, 0);
INSERT INTO "T_INFORMATION_INF" (version, "INF_NAME", "INF_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "INF_VALUE_NUM", "INF_INU_INU_ID") VALUES (0, 'Memory Swap free', NULL, 6, 1, 1, 1, 0);
--
-- TOC entry 2378 (class 0 OID 34902)
-- Dependencies: 185 2411
-- Data for Name: T_SEARCH_PARAMETER_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SEARCH_PARAMETER_SEP" ("SEP_ID", version, "SEP_FORMAT", "SEP_NAME", "SEP_DELETE") VALUES (0, 0, 'text', 'regex', NULL);


--
-- TOC entry 2402 (class 0 OID 35291)
-- Dependencies: 226 2378 2357 2411
-- Data for Name: TJ_STY_SEP; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "TJ_STY_SEP" ("T_SEARCH_TYPE_STY_STY_ID", "T_SEARCH_PARAMETER_SEP_SEP_ID") VALUES (0, 0);

--
-- TOC entry 2391 (class 0 OID 35104)
-- Dependencies: 208 2378 2358 2411
-- Data for Name: T_SEARCH_PARAMETER_VALUE_SEV; Type: TABLE DATA; Schema: public; Owner: echoes
--

-- INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, "^MemTotal:\\s+([0-9]+)\\skB", NULL, 1, 1, 1, 0);
-- INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, "^MemFree:\s+([0-9]+)\skB", NULL, 2, 1, 1, 0);
 --INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, "^Buffers:\s+([0-9]+)\skB", NULL, 3, 1, 1, 0);

 --INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, "^Cached:\s+([0-9]+)\skB", NULL, 4, 1, 1, 0);
 --INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, "^SwapTotal:\s+([0-9]+)\skB", NULL, 5, 1, 1, 0);
 --INSERT INTO "T_SEARCH_PARAMETER_VALUE_SEV" (version, "SEV_VALUE", "SEV_DELETE", "SEA_ID", "SRC_ID", "PLG_ID_PLG_ID", "SEP_ID_SEP_ID") VALUES (0, "^SwapFree:\s+([0-9]+)\skB", NULL, 6, 1, 1, 0);
--
-- TOC entry 2392 (class 0 OID 35122)
-- Dependencies: 209 2356 2379 2411
-- Data for Name: T_SOURCE_PARAMETER_VALUE_SPV; Type: TABLE DATA; Schema: public; Owner: echoes
--

INSERT INTO "T_SOURCE_PARAMETER_VALUE_SPV" (version, "SPV_VALUE", "SPV_DELETE", "SRP_ID_SRP_ID", "SRC_ID", "PLG_ID_PLG_ID") VALUES (0, '/proc/meminfo', NULL, 0, 1, 1);


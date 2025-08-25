--
-- PostgreSQL database dump
--

-- Dumped from database version 15.13 (Debian 15.13-0+deb12u1)
-- Dumped by pg_dump version 15.13

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: comp_configs; Type: TABLE; Schema: public; Owner: user
--

CREATE TABLE public.comp_configs (
    compose_date date NOT NULL,
    mb_ram integer NOT NULL,
    cpu character varying(25),
    code integer NOT NULL
);


ALTER TABLE public.comp_configs OWNER TO "user";

--
-- Name: comp_configs_code_seq; Type: SEQUENCE; Schema: public; Owner: user
--

CREATE SEQUENCE public.comp_configs_code_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.comp_configs_code_seq OWNER TO "user";

--
-- Name: comp_configs_code_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: user
--

ALTER SEQUENCE public.comp_configs_code_seq OWNED BY public.comp_configs.code;


--
-- Name: computers; Type: TABLE; Schema: public; Owner: user
--

CREATE TABLE public.computers (
    name character varying(255) DEFAULT 'no name'::character varying NOT NULL,
    config integer,
    code bigint NOT NULL
);


ALTER TABLE public.computers OWNER TO "user";

--
-- Name: comps_sequence; Type: SEQUENCE; Schema: public; Owner: user
--

CREATE SEQUENCE public.comps_sequence
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.comps_sequence OWNER TO "user";

--
-- Name: comps_sequence; Type: SEQUENCE OWNED BY; Schema: public; Owner: user
--

ALTER SEQUENCE public.comps_sequence OWNED BY public.computers.code;

-- Name: cpus; Type: TABLE; Schema: public; Owner: user
--

CREATE TABLE public.cpus (
    code character varying(25) NOT NULL,
    threads integer DEFAULT 1 NOT NULL,
    cores integer DEFAULT 1 NOT NULL
);


ALTER TABLE public.cpus OWNER TO "user";

--
-- Name: report; Type: VIEW; Schema: public; Owner: user
--

CREATE VIEW public.report AS
 SELECT comp.code,
    comp.name,
    config.cpu,
    config.mb_ram,
    config.compose_date
   FROM (public.computers comp
     LEFT JOIN public.comp_configs config ON ((comp.config = config.code)))
  ORDER BY comp.code;


ALTER TABLE public.report OWNER TO "user";

--
-- Name: comp_configs code; Type: DEFAULT; Schema: public; Owner: user
--

ALTER TABLE ONLY public.comp_configs ALTER COLUMN code SET DEFAULT nextval('public.comp_configs_code_seq'::regclass);


--
-- Name: computers code; Type: DEFAULT; Schema: public; Owner: user
--

ALTER TABLE ONLY public.computers ALTER COLUMN code SET DEFAULT nextval('public.comps_sequence'::regclass);


--
-- Data for Name: comp_configs; Type: TABLE DATA; Schema: public; Owner: user
--

COPY public.comp_configs (compose_date, mb_ram, cpu, code) FROM stdin;
2023-01-27	768	i7-2630QM	1
2024-06-27	16536	not defined	2
\.


--
-- Data for Name: computers; Type: TABLE DATA; Schema: public; Owner: user
--

COPY public.computers (name, config, code) FROM stdin;
Stretch	1	1
freevm	2	2
\.


--
-- Data for Name: cpus; Type: TABLE DATA; Schema: public; Owner: user
--

COPY public.cpus (code, threads, cores) FROM stdin;
i7-2630QM	8	4
not defined	0	0
\.


--
-- Name: comp_configs_code_seq; Type: SEQUENCE SET; Schema: public; Owner: user
--

SELECT pg_catalog.setval('public.comp_configs_code_seq', 2, true);


--
-- Name: comps_sequence; Type: SEQUENCE SET; Schema: public; Owner: user
--

SELECT pg_catalog.setval('public.comps_sequence', 2, false);


--
-- Name: computers code_pk; Type: CONSTRAINT; Schema: public; Owner: user
--

ALTER TABLE ONLY public.computers
    ADD CONSTRAINT code_pk PRIMARY KEY (code);


--
-- Name: comp_configs config_pkey; Type: CONSTRAINT; Schema: public; Owner: user
--

ALTER TABLE ONLY public.comp_configs
    ADD CONSTRAINT config_pkey PRIMARY KEY (code);


--
-- Name: cpus pk_code; Type: CONSTRAINT; Schema: public; Owner: user
--

ALTER TABLE ONLY public.cpus
    ADD CONSTRAINT pk_code PRIMARY KEY (code);


--
-- Name: comp_name_idx; Type: INDEX; Schema: public; Owner: user
--

CREATE INDEX comp_name_idx ON public.computers USING btree (name);


--
-- Name: cpu_code_fkey; Type: INDEX; Schema: public; Owner: user
--

CREATE INDEX cpu_code_fkey ON public.comp_configs USING btree (cpu);


--
-- Name: fki_config_fk; Type: INDEX; Schema: public; Owner: user
--

CREATE INDEX fki_config_fk ON public.computers USING btree (config);


--
-- Name: computers config_fk; Type: FK CONSTRAINT; Schema: public; Owner: user
--

ALTER TABLE ONLY public.computers
    ADD CONSTRAINT config_fk FOREIGN KEY (config) REFERENCES public.comp_configs(code);


--
-- Name: comp_configs cpu_code; Type: FK CONSTRAINT; Schema: public; Owner: user
--

ALTER TABLE ONLY public.comp_configs
    ADD CONSTRAINT cpu_code FOREIGN KEY (cpu) REFERENCES public.cpus(code);


--
-- PostgreSQL database dump complete
--


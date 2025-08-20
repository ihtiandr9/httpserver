﻿--
-- PostgreSQL database dump
--

-- Dumped from database version 17.5
-- Dumped by pg_dump version 17.5

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
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
    cpu character(15) NOT NULL,
    comp_code character(9) NOT NULL,
    compose_date date NOT NULL,
    mb_ram integer NOT NULL
);


ALTER TABLE public.comp_configs OWNER TO "user";

--
-- Name: comps_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.comps_seq
    START WITH 1
    INCREMENT BY 1
    MINVALUE 0
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.comps_seq OWNER TO postgres;

--
-- Name: computers; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.computers (
    name character varying(255) DEFAULT 'no name'::character varying NOT NULL,
    code character(9) DEFAULT nextval('public.comps_seq'::regclass) NOT NULL
);


ALTER TABLE public.computers OWNER TO postgres;

--
-- Name: report; Type: VIEW; Schema: public; Owner: user
--

CREATE VIEW public.report AS
 SELECT comp.code,
    comp.name,
    conf.cpu,
    conf.mb_ram
   FROM (public.computers comp
     JOIN public.comp_configs conf ON ((comp.code = conf.comp_code)));


ALTER VIEW public.report OWNER TO "user";

--
-- Data for Name: comp_configs; Type: TABLE DATA; Schema: public; Owner: user
--

COPY public.comp_configs (cpu, comp_code, compose_date, mb_ram) FROM stdin;
1              	10       	2023-01-27	4096
1              	11       	2023-01-27	768
\.


--
-- Data for Name: computers; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.computers (name, code) FROM stdin;
freevm	10       
Stretch	11       
not composed	12       
\.


--
-- Name: comps_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.comps_seq', 12, true);


--
-- Name: computers code_pk; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.computers
    ADD CONSTRAINT code_pk PRIMARY KEY (code);


--
-- Name: comp_configs config_pkey; Type: CONSTRAINT; Schema: public; Owner: user
--

ALTER TABLE ONLY public.comp_configs
    ADD CONSTRAINT config_pkey PRIMARY KEY (comp_code, compose_date);


--
-- Name: comp_name_idx; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX comp_name_idx ON public.computers USING btree (name);


--
-- Name: comp_configs comp_code_fkey; Type: FK CONSTRAINT; Schema: public; Owner: user
--

ALTER TABLE ONLY public.comp_configs
    ADD CONSTRAINT comp_code_fkey FOREIGN KEY (comp_code) REFERENCES public.computers(code);


--
-- PostgreSQL database dump complete
--


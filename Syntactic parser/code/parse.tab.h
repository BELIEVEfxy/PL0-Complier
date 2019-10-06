/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     IF = 258,
     DO = 259,
     ENDD = 260,
     VAR = 261,
     ODD = 262,
     THEN = 263,
     READ = 264,
     CALL = 265,
     WHILE = 266,
     BEG = 267,
     BREAK = 268,
     CONST = 269,
     WRITE = 270,
     PROCEDURE = 271,
     FOR = 272,
     TO = 273,
     ID = 274,
     NUM = 275,
     WRONGID = 276,
     SEMICOLON = 277,
     COMMA = 278,
     EOP = 279,
     COLON = 280,
     LPARAN = 281,
     RPARAN = 282,
     PLUS = 283,
     MINUS = 284,
     MULTIPLY = 285,
     DIVISION = 286,
     ASSIGN = 287,
     GREAT = 288,
     LESS = 289,
     GE = 290,
     LE = 291,
     EQ = 292,
     NEQ = 293
   };
#endif
/* Tokens.  */
#define END 0
#define IF 258
#define DO 259
#define ENDD 260
#define VAR 261
#define ODD 262
#define THEN 263
#define READ 264
#define CALL 265
#define WHILE 266
#define BEG 267
#define BREAK 268
#define CONST 269
#define WRITE 270
#define PROCEDURE 271
#define FOR 272
#define TO 273
#define ID 274
#define NUM 275
#define WRONGID 276
#define SEMICOLON 277
#define COMMA 278
#define EOP 279
#define COLON 280
#define LPARAN 281
#define RPARAN 282
#define PLUS 283
#define MINUS 284
#define MULTIPLY 285
#define DIVISION 286
#define ASSIGN 287
#define GREAT 288
#define LESS 289
#define GE 290
#define LE 291
#define EQ 292
#define NEQ 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 89 "parse.y"
{
    int number;
    char* str;
}
/* Line 1529 of yacc.c.  */
#line 132 "parse.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 4 "parse.y"
 /*** C/C++ Declarations ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

/* define max stack size */
#define STACK_MAXN 1024000
/* define max identifier size */
#define ID_MAX_SIZE 102400
/* define max type */
#define TYPE_MAXN 1024

/* stack for node 
********************
* struct node:
* @para int_32 type : type of the node 
* @para int_32 val : int value of the node
* @para char*  id  : string value of the node
* @para int_32 childcnt : child amound
* @para node** child : child node
********************
*/
char infile[32];
char *outfile;
FILE *fin;
FILE *fout;
extern FILE * yyin;
extern FILE * yyout;

Node* stack[STACK_MAXN+1];

/* top of the stack */
int stop;

/* child_type array and cnt for parameter pass */
int child_tp[TYPE_MAXN];
int child_tp_cnt;

/* function for stack */
void push( Node* );
void pop();
void freenode(Node*);
int empty();
Node* top();

/* function for print */
void print_node( Node*, int );
void show_child(Node*);

/* void shift 
* add a new node to the stack
* @para type: new node type.
* @para id: string value of new node.
* @para number: int_32 value of new node.
*/
void shift(int type,char* id,int number);

/* void reduce
* release the node in the stack to form the new node.
* @para type: new node type.
* @para child_type_cnt: amount of child types. type see header.h
* @para child_type[]: type array.
* this function find the new node's child and pop them from the stack
* and push the new node into it.
*/
void reduce(int type, int child_type_cnt, int child_type[TYPE_MAXN]);

/* utils function */
void node_copy(Node* copy,Node* copied);
int inarray(int tp,int tpcnt, int tparray[TYPE_MAXN]);
int yylex();
/* redefine yyerror */
void yyerror(const char *str)
{
        fprintf(stderr,"error: %s\n",str);
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 89 "parse.y"
{
    int number;
    char* str;
}
/* Line 193 of yacc.c.  */
#line 259 "parse.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 272 "parse.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   121

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNRULES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     9,    14,    15,    20,    21,    25,
      26,    27,    35,    36,    42,    43,    44,    49,    50,    51,
      57,    58,    62,    64,    66,    68,    70,    72,    74,    76,
      78,    80,    82,    83,    84,    85,    91,    92,    97,    99,
     100,   105,   106,   107,   114,   118,   119,   123,   126,   130,
     133,   135,   137,   138,   143,   147,   148,   151,   152,   154,
     156,   158,   160,   162,   164,   166,   168,   170,   172,   173,
     174,   181,   182,   183,   184,   194,   197,   198,   199,   206,
     208,   212,   213,   214,   221,   223,   224
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    -1,    42,    24,    41,     0,    -1,    43,
      48,    52,    55,    -1,    -1,    14,    44,    45,    22,    -1,
      -1,    19,    37,    20,    -1,    -1,    -1,    19,    37,    20,
      46,    23,    47,    45,    -1,    -1,     6,    19,    49,    50,
      22,    -1,    -1,    -1,    23,    19,    51,    50,    -1,    -1,
      -1,    54,    42,    53,    22,    52,    -1,    -1,    16,    19,
      22,    -1,    56,    -1,    57,    -1,    58,    -1,    63,    -1,
      65,    -1,    79,    -1,    82,    -1,    86,    -1,    87,    -1,
      91,    -1,    -1,    -1,    -1,    19,    59,    32,    60,    70,
      -1,    -1,    55,    22,    62,    61,    -1,    55,    -1,    -1,
      12,    64,    61,     5,    -1,    -1,    -1,     3,    66,    68,
       8,    67,    55,    -1,    70,    78,    70,    -1,    -1,     7,
      69,    70,    -1,    71,    74,    -1,    76,    71,    74,    -1,
      72,    75,    -1,    19,    -1,    20,    -1,    -1,    26,    73,
      70,    27,    -1,    76,    71,    74,    -1,    -1,    77,    72,
      -1,    -1,    28,    -1,    29,    -1,    30,    -1,    31,    -1,
      37,    -1,    38,    -1,    34,    -1,    33,    -1,    35,    -1,
      36,    -1,    -1,    -1,    11,    80,    68,     4,    81,    55,
      -1,    -1,    -1,    -1,    17,    83,    58,    18,    84,    68,
       4,    85,    55,    -1,    10,    19,    -1,    -1,    -1,     9,
      88,    26,    89,    90,    27,    -1,    19,    -1,    19,    23,
      90,    -1,    -1,    -1,    15,    92,    26,    93,    94,    27,
      -1,    70,    -1,    -1,    70,    23,    95,    94,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   139,   149,   160,   160,   170,   173,   188,
     193,   186,   207,   206,   218,   222,   221,   231,   234,   234,
     241,   244,   257,   263,   266,   272,   278,   284,   290,   296,
     302,   308,   317,   320,   321,   320,   333,   332,   342,   350,
     350,   362,   363,   362,   375,   383,   383,   393,   400,   410,
     419,   426,   433,   433,   446,   455,   458,   465,   468,   475,
     484,   491,   500,   507,   514,   521,   528,   535,   544,   546,
     544,   558,   560,   562,   558,   576,   588,   589,   588,   602,
     609,   621,   622,   621,   635,   641,   641
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "\"if\"", "\"do\"", "\"end\"",
  "\"var\"", "\"odd\"", "\"then\"", "\"read\"", "\"call\"", "\"while\"",
  "\"begin\"", "\"break\"", "\"const\"", "\"write\"", "\"procedure\"",
  "\"for\"", "\"to\"", "\"id\"", "\"number\"", "\"wrong_id\"", "\";\"",
  "\",\"", "\".\"", "\":\"", "\"(\"", "\")\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\":=\"", "\">\"", "\"<\"", "\">=\"", "\"<=\"", "\"=\"",
  "\"#\"", "$accept", "program", "@1", "subprogram", "constInstruction",
  "@2", "constDeclaration", "@3", "@4", "variableInstruction", "@5",
  "variableInstructionSuf", "@6", "procedureInstruction", "@7",
  "procedureHeader", "sentence", "unemptysentence", "emptysentence",
  "assignment", "@8", "@9", "multsentence", "@10", "compound", "@11",
  "conditional", "@12", "@13", "condition", "@14", "expr", "item",
  "factor", "@15", "itemsuf", "factorsuf", "plusop", "mulop", "relationop",
  "whileLoop", "@16", "@17", "forLoop", "@18", "@19", "@20",
  "procedureCall", "readSent", "@21", "@22", "readpara", "writeSent",
  "@23", "@24", "writepara", "@25", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    41,    40,    42,    44,    43,    43,    45,    46,
      47,    45,    49,    48,    48,    51,    50,    50,    53,    52,
      52,    54,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    57,    59,    60,    58,    62,    61,    61,    64,
      63,    66,    67,    65,    68,    69,    68,    70,    70,    71,
      72,    72,    73,    72,    74,    74,    75,    75,    76,    76,
      77,    77,    78,    78,    78,    78,    78,    78,    80,    81,
      79,    83,    84,    85,    82,    86,    88,    89,    87,    90,
      90,    92,    93,    91,    94,    95,    94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     4,     0,     4,     0,     3,     0,
       0,     7,     0,     5,     0,     0,     4,     0,     0,     5,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     0,     0,     5,     0,     4,     1,     0,
       4,     0,     0,     6,     3,     0,     3,     2,     3,     2,
       1,     1,     0,     4,     3,     0,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     0,
       6,     0,     0,     0,     9,     2,     0,     0,     6,     1,
       3,     0,     0,     6,     1,     0,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,     5,     0,     0,    14,     0,     1,     2,     0,    20,
       0,     0,     0,    12,     0,    32,     7,     0,     6,     3,
      17,     0,    41,    76,     0,    68,    39,    81,    71,    33,
       4,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    18,     8,     0,     0,    21,     0,     0,    75,     0,
      32,     0,     0,     0,     0,     0,    15,    13,    45,    50,
      51,    52,    58,    59,     0,     0,    55,    57,     0,    77,
       0,    38,     0,    82,     0,    34,    20,    10,    17,     0,
       0,    42,    65,    64,    66,    67,    62,    63,     0,    47,
       0,    60,    61,    49,     0,    55,     0,    69,    36,    40,
       0,    72,     0,    19,     0,    16,    46,     0,    32,    44,
      55,    56,    48,    79,     0,    32,    32,    84,     0,     0,
      35,    11,    53,    43,    54,     0,    78,    70,    37,    85,
      83,     0,    80,     0,    73,    86,    32,    74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    12,     3,     4,     5,    11,    55,   104,     9,
      20,    44,    78,    15,    54,    16,    71,    31,    32,    33,
      53,   102,    72,   116,    34,    50,    35,    46,   108,    64,
      79,    65,    66,    67,    80,    89,    93,    68,    94,    88,
      36,    49,   115,    37,    52,   119,   136,    38,    39,    47,
      96,   114,    40,    51,   100,   118,   133
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -90
static const yytype_int8 yypact[] =
{
      -4,   -90,    14,    -8,    13,     1,   -90,   -90,     3,    16,
       2,    19,    38,   -90,    28,    25,    -4,    23,   -90,   -90,
      27,    29,   -90,   -90,    30,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,    40,    34,    42,   -90,    -2,    39,   -90,    -2,
      25,    41,    47,    36,    48,    46,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,    64,    24,   -16,     0,   -11,   -90,
      69,    52,    70,   -90,    58,   -90,    16,   -90,    27,    26,
      26,   -90,   -90,   -90,   -90,   -90,   -90,   -90,    26,   -90,
     -11,   -90,   -90,   -90,   -11,   -16,    59,   -90,   -90,   -90,
      26,   -90,    26,   -90,     1,   -90,   -90,    50,    25,   -90,
     -16,   -90,   -90,    56,    53,    25,    25,    60,    54,    -2,
     -90,   -90,   -90,   -90,   -90,    59,   -90,   -90,   -90,   -90,
     -90,    78,   -90,    26,   -90,   -90,    25,   -90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -90,   -90,   -90,    68,   -90,   -90,   -19,   -90,   -90,   -90,
     -90,     8,   -90,    11,   -90,   -90,   -15,   -90,   -90,    37,
     -90,   -90,   -28,   -90,   -90,   -90,   -90,   -90,   -90,   -48,
     -90,   -77,   -61,    -3,   -90,   -89,   -90,   -62,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -35,   -90,   -90,   -90,   -41,   -90
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -10
static const yytype_int16 yytable[] =
{
      30,    70,   106,   107,    90,    58,   112,    95,    59,    60,
       1,   109,    62,    63,     6,    61,     7,    59,    60,     8,
      10,   124,    13,   117,    61,   120,    62,    63,    22,   110,
      91,    92,    14,    90,    23,    24,    25,    26,    19,    17,
      27,    18,    28,    42,    29,    59,    60,    21,    90,    48,
      43,    45,    61,    56,    62,    63,   117,    82,    83,    84,
      85,    86,    87,    -9,    57,    69,    29,    73,    75,    77,
      76,   131,    81,    97,    98,    99,   101,   122,   113,   125,
     126,   130,   134,   129,    41,   121,   105,   103,   128,    74,
     132,   111,   135,   123,     0,     0,     0,     0,     0,     0,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   137
};

static const yytype_int16 yycheck[] =
{
      15,    49,    79,    80,    66,     7,    95,    68,    19,    20,
      14,    88,    28,    29,     0,    26,    24,    19,    20,     6,
      19,   110,    19,   100,    26,   102,    28,    29,     3,    90,
      30,    31,    16,    95,     9,    10,    11,    12,     0,    37,
      15,    22,    17,    20,    19,    19,    20,    19,   110,    19,
      23,    22,    26,    19,    28,    29,   133,    33,    34,    35,
      36,    37,    38,    23,    22,    26,    19,    26,    32,    23,
      22,   119,     8,     4,    22,     5,    18,    27,    19,    23,
      27,    27,     4,    23,    16,   104,    78,    76,   116,    52,
     125,    94,   133,   108,    -1,    -1,    -1,    -1,    -1,    -1,
     115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   136
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    40,    42,    43,    44,     0,    24,     6,    48,
      19,    45,    41,    19,    16,    52,    54,    37,    22,     0,
      49,    19,     3,     9,    10,    11,    12,    15,    17,    19,
      55,    56,    57,    58,    63,    65,    79,    82,    86,    87,
      91,    42,    20,    23,    50,    22,    66,    88,    19,    80,
      64,    92,    83,    59,    53,    46,    19,    22,     7,    19,
      20,    26,    28,    29,    68,    70,    71,    72,    76,    26,
      68,    55,    61,    26,    58,    32,    22,    23,    51,    69,
      73,     8,    33,    34,    35,    36,    37,    38,    78,    74,
      76,    30,    31,    75,    77,    71,    89,     4,    22,     5,
      93,    18,    60,    52,    47,    50,    70,    70,    67,    70,
      71,    72,    74,    19,    90,    81,    62,    70,    94,    84,
      70,    45,    27,    55,    74,    23,    27,    55,    61,    23,
      27,    68,    90,    95,     4,    94,    85,    55
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 139 "parse.y"
    {shift(EOP_OP, ".", 0);;}
    break;

  case 3:
#line 140 "parse.y"
    {
                            child_tp_cnt = 2;
                            child_tp[0] = SUBPROGRAM;
                            child_tp[1] = EOP_OP;
                            reduce(PROGRAM, child_tp_cnt, child_tp);
                            fprintf(fout, "program -> subprogram.\n");
                            ;}
    break;

  case 4:
#line 149 "parse.y"
    { 
                                                                                child_tp_cnt = 4;
                                                                                child_tp[0] = CONST_INSTRUCTION;
                                                                                child_tp[1] = VARIABLE_INSTRUCTION;
                                                                                child_tp[2] = PROCEDURE_INSTRUCTION;
                                                                                child_tp[3] = SENTENCE;
                                                                                reduce(SUBPROGRAM, child_tp_cnt, child_tp);
                                                                                fprintf(fout, "subprogram -> constInstruction variableInstruction procedureInstruction sentence\n");
                                                                                ;}
    break;

  case 5:
#line 160 "parse.y"
    {shift(CONST_KEY,(yyvsp[(1) - (1)].str),0);;}
    break;

  case 6:
#line 161 "parse.y"
    {
                                            shift(SEMI_OP,";",0);
                                            child_tp_cnt = 3; 
                                            child_tp[0] = CONST_KEY;
                                            child_tp[1] = CONST_DECLARATION; 
                                            child_tp[2] = SEMI_OP;
                                            reduce(CONST_INSTRUCTION,child_tp_cnt,child_tp);
                                            fprintf(fout, "constInstruction -> CONST constDeclaration;\n");
                                            ;}
    break;

  case 8:
#line 175 "parse.y"
    {
                                shift(IDENTI, (yyvsp[(1) - (3)].str), 0);
                                shift(EQ_OP, "=", 0);
                                shift(NUMBER, NULL,(yyvsp[(3) - (3)].number));
                                child_tp_cnt = 3; 
                                child_tp[0]=IDENTI;
                                child_tp[1]=EQ_OP;
                                child_tp[2]=NUMBER; 
                                reduce(CONST_DECLARATION, child_tp_cnt, child_tp);
                                fprintf(fout, "constDeclaration -> ID = NUMBER\n");
                                ;}
    break;

  case 9:
#line 188 "parse.y"
    {
                                        shift(IDENTI, (yyvsp[(1) - (3)].str), 0);
                                        shift(EQ_OP, "=", 0);
                                        shift(NUMBER, NULL,(yyvsp[(3) - (3)].number));
                                        ;}
    break;

  case 10:
#line 193 "parse.y"
    {shift(COMMA_OP, ",", 0);;}
    break;

  case 11:
#line 194 "parse.y"
    {
                                        child_tp_cnt = 5;
                                        child_tp[0] = IDENTI;
                                        child_tp[1] = EQ_OP;
                                        child_tp[2] = NUMBER;
                                        child_tp[3] = COMMA_OP;
                                        child_tp[4] = CONST_DECLARATION;
                                        reduce(CONST_DECLARATION, child_tp_cnt, child_tp);
                                        fprintf(fout, "constDeclaration -> ID = NUMBER , constDeclaration\n");
                                        ;}
    break;

  case 12:
#line 207 "parse.y"
    {shift(VAR_KEY,(yyvsp[(1) - (2)].str),0);shift(IDENTI,(yyvsp[(2) - (2)].str),0);;}
    break;

  case 13:
#line 208 "parse.y"
    {
                                                    shift(SEMI_OP,";",0);
                                                    child_tp_cnt = 4; 
                                                    child_tp[0] = VAR_KEY;
                                                    child_tp[1] = IDENTI;
                                                    child_tp[2] = VARIABLE_INSTRUCTIONSUF;
                                                    child_tp[3] = SEMI_OP; 
                                                    reduce(VARIABLE_INSTRUCTION,child_tp_cnt,child_tp);
                                                    fprintf(fout, "variableInstruction -> VAR ID variableInstructionSuf ;\n");
                                                    ;}
    break;

  case 15:
#line 222 "parse.y"
    {shift(COMMA_OP, ",", 0);shift(IDENTI,(yyvsp[(2) - (2)].str),0);;}
    break;

  case 16:
#line 223 "parse.y"
    {
                                                    child_tp_cnt = 3;
                                                    child_tp[0] = COMMA_OP;
                                                    child_tp[1] = IDENTI;
                                                    child_tp[2] = VARIABLE_INSTRUCTIONSUF;
                                                    reduce(VARIABLE_INSTRUCTIONSUF, child_tp_cnt, child_tp);
                                                    fprintf(fout, "variableInstructionSuf -> , ID variableInstructionSuf \n");
                                                    ;}
    break;

  case 18:
#line 234 "parse.y"
    {
                                                    child_tp_cnt = 2; 
                                                    child_tp[0] = PROCEDURE_HEADER; 
                                                    child_tp[1] = SUBPROGRAM; 
                                                    reduce(PROCEDURE_INSTRUCTION,child_tp_cnt,child_tp);
                                                    ;}
    break;

  case 19:
#line 240 "parse.y"
    {fprintf(fout, "procedureInstruction -> procedureHeader subprogram ; procedureInstruction\n");;}
    break;

  case 21:
#line 244 "parse.y"
    {
                                        shift(PROCEDURE_KEY,(yyvsp[(1) - (3)].str),0);
                                        shift(IDENTI,(yyvsp[(2) - (3)].str),0);
                                        shift(SEMI_OP,";",0);
                                        child_tp_cnt = 3;
                                        child_tp[0] = PROCEDURE_KEY;
                                        child_tp[1] = IDENTI;
                                        child_tp[2] = SEMI_OP;
                                        reduce(PROCEDURE_HEADER,child_tp_cnt,child_tp);
                                        fprintf(fout, "procedureHeader -> PROCEDURE ID ;\n");
                                        ;}
    break;

  case 22:
#line 257 "parse.y"
    {
                            child_tp_cnt = 1;
                            child_tp[0] = UNEMPTY_SENTENCE;
                            reduce(SENTENCE, child_tp_cnt,child_tp);
                            fprintf(fout, "sentence -> unemptysentence\n");
                            ;}
    break;

  case 23:
#line 263 "parse.y"
    { ;}
    break;

  case 24:
#line 266 "parse.y"
    {
                                child_tp_cnt = 1;
                                child_tp[0] = ASSIGNMENT;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> assignment\n");
                                ;}
    break;

  case 25:
#line 272 "parse.y"
    {
                                child_tp_cnt = 1;
                                child_tp[0] = COMPOUND;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> compound\n");
                                ;}
    break;

  case 26:
#line 278 "parse.y"
    {
                                child_tp_cnt = 1;
                                child_tp[0] = CONDITIONAL;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> conditional\n");
                                ;}
    break;

  case 27:
#line 284 "parse.y"
    {
                                child_tp_cnt = 1;
                                child_tp[0] = WHILELOOP;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> whileLoop\n");
                                ;}
    break;

  case 28:
#line 290 "parse.y"
    {
                                child_tp_cnt = 1;
                                child_tp[0] = FORLOOP;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> forLoop\n");
                                ;}
    break;

  case 29:
#line 296 "parse.y"
    {
                                child_tp_cnt = 1;
                                child_tp[0] = PROCEDURE_CALL;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> procedureCall\n");
                                ;}
    break;

  case 30:
#line 302 "parse.y"
    {
                                child_tp_cnt = 1;
                                child_tp[0] = READ_SENTENCE;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> readSent\n");
                                ;}
    break;

  case 31:
#line 308 "parse.y"
    {
                                child_tp_cnt = 1;
                                child_tp[0] = WRITE_SENTENCE;
                                reduce(UNEMPTY_SENTENCE, child_tp_cnt, child_tp);
                                fprintf(fout, "unemptysentence -> writeSent\n");
                                ;}
    break;

  case 33:
#line 320 "parse.y"
    {shift(IDENTI,(yyvsp[(1) - (1)].str),0);;}
    break;

  case 34:
#line 321 "parse.y"
    {shift(ASSIGN_OP,":=",0);;}
    break;

  case 35:
#line 322 "parse.y"
    { 
                        child_tp_cnt = 3;
                        child_tp[0] = IDENTI;
                        child_tp[1] = ASSIGN_OP;
                        child_tp[2] = EXPRESSION;
                        reduce(ASSIGNMENT, child_tp_cnt, child_tp);
                        fprintf(fout, "assignment -> ID := expr\n");
                        ;}
    break;

  case 36:
#line 333 "parse.y"
    {
                                child_tp_cnt = 2;
                                child_tp[0] = SENTENCE;
                                child_tp[1] = SEMI_OP;
                                reduce(MULTI_SENTENCE, child_tp_cnt, child_tp);
                                ;}
    break;

  case 37:
#line 339 "parse.y"
    {          
                                
                                ;}
    break;

  case 38:
#line 342 "parse.y"
    {
                                child_tp_cnt = 1;
                                child_tp[0] = SENTENCE;
                                reduce(MULTI_SENTENCE, child_tp_cnt, child_tp);
                                
                                ;}
    break;

  case 39:
#line 350 "parse.y"
    {shift(BEGIN_KEY,"begin",0);;}
    break;

  case 40:
#line 351 "parse.y"
    { 
                                shift(END_KEY,"end",0);
                                child_tp_cnt = 3;
                                child_tp[0] = BEGIN_KEY;
                                child_tp[1] = MULTI_SENTENCE;
                                child_tp[2] = END_KEY;
                                reduce(COMPOUND, child_tp_cnt, child_tp);
                                fprintf(fout, "compound -> BEGIN multsentence END\n");
                                ;}
    break;

  case 41:
#line 362 "parse.y"
    {shift(IF_KEY,"if",0);;}
    break;

  case 42:
#line 363 "parse.y"
    {shift(THEN_KEY,"then",0);;}
    break;

  case 43:
#line 364 "parse.y"
    {
                                child_tp_cnt = 4;
                                child_tp[0] = IF_KEY;
                                child_tp[1] = CONDITION;
                                child_tp[2] = THEN_KEY;
                                child_tp[3] = SENTENCE;
                                reduce(CONDITIONAL, child_tp_cnt, child_tp);
                                fprintf(fout, "comditional -> IF condition THEN sentence\n");
                                ;}
    break;

  case 44:
#line 375 "parse.y"
    {
                                    child_tp_cnt = 3;
                                    child_tp[0] = EXPRESSION;
                                    child_tp[1] = RELATION_OPERATOR;
                                    child_tp[2] = EXPRESSION;
                                    reduce(CONDITION, child_tp_cnt, child_tp);
                                    fprintf(fout, "condition -> expr relationop expr\n");
                                    ;}
    break;

  case 45:
#line 383 "parse.y"
    {shift(ODD_KEY, "odd", 0);;}
    break;

  case 46:
#line 384 "parse.y"
    {
                                    child_tp_cnt = 2;
                                    child_tp[0] = ODD_KEY;
                                    child_tp[1] = EXPRESSION;
                                    reduce(CONDITION, child_tp_cnt, child_tp);
                                    fprintf(fout, "condition -> ODD expr\n");
                                    ;}
    break;

  case 47:
#line 393 "parse.y"
    {
                                child_tp_cnt = 2;
                                child_tp[0] = ITEM;
                                child_tp[1] = ITEM_SUF;
                                reduce(EXPRESSION, child_tp_cnt, child_tp);
                                fprintf(fout, "expr -> item itemsuf\n");
                                ;}
    break;

  case 48:
#line 400 "parse.y"
    {
                                child_tp_cnt = 3;
                                child_tp[0] = PLUS_OPERATOR;
                                child_tp[1] = ITEM;
                                child_tp[2] = ITEM_SUF;
                                reduce(EXPRESSION, child_tp_cnt, child_tp);
                                fprintf(fout, "expr -> plusop item itemsuf\n");
                                ;}
    break;

  case 49:
#line 410 "parse.y"
    {
                        child_tp_cnt = 2;
                        child_tp[0] = FACTOR;
                        child_tp[1] = FACTOR_SUFFIX;
                        reduce(ITEM, child_tp_cnt, child_tp);
                        fprintf(fout, "item -> factor factorsuf\n");
                        ;}
    break;

  case 50:
#line 419 "parse.y"
    {
                    shift(IDENTI, (yyvsp[(1) - (1)].str), 0);
                    child_tp_cnt = 1;
                    child_tp[0] = IDENTI;
                    reduce(FACTOR, child_tp_cnt, child_tp);
                    fprintf(fout, "factor -> ID\n");
                    ;}
    break;

  case 51:
#line 426 "parse.y"
    {
                    shift(NUMBER, NULL, (yyvsp[(1) - (1)].number));
                    child_tp_cnt = 1;
                    child_tp[0] = NUMBER;
                    reduce(FACTOR, child_tp_cnt, child_tp);
                    fprintf(fout, "factor -> NUMBER\n");
                    ;}
    break;

  case 52:
#line 433 "parse.y"
    {shift(LEFTPARAN, "(", 0);;}
    break;

  case 53:
#line 435 "parse.y"
    {
                    shift(RIGHTPARAN, ")", 0);
                    child_tp_cnt = 3;
                    child_tp[0] = LEFTPARAN;
                    child_tp[1] = EXPRESSION;
                    child_tp[2] = RIGHTPARAN;
                    reduce(FACTOR, child_tp_cnt, child_tp);
                    fprintf(fout, "factor -> (expr) \n");
                    ;}
    break;

  case 54:
#line 447 "parse.y"
    {
                        child_tp_cnt = 3;
                        child_tp[0] = PLUS_OPERATOR;
                        child_tp[1] = ITEM;
                        child_tp[2] = ITEM_SUF;
                        reduce(ITEM_SUF, child_tp_cnt, child_tp);
                        fprintf(fout, "itemsuf -> plusop item itemsuf\n");
                        ;}
    break;

  case 56:
#line 458 "parse.y"
    {
                            child_tp_cnt = 2;
                            child_tp[0] = MULTIPLY_OPERATOR;
                            child_tp[1] = FACTOR;
                            reduce(FACTOR_SUFFIX, child_tp_cnt, child_tp);
                            fprintf(fout, "factorsuf -> mulop factor factorsuf\n");
                            ;}
    break;

  case 58:
#line 468 "parse.y"
    {
                    shift(PLUS_OP, "+", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = PLUS_OP;
                    reduce(PLUS_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> +\n");
                    ;}
    break;

  case 59:
#line 475 "parse.y"
    {
                    shift(MINUS_OP, "-", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = MINUS_OP;
                    reduce(PLUS_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> -\n");
                    ;}
    break;

  case 60:
#line 484 "parse.y"
    {
                shift(MUL_OP, "*", 0);
                child_tp_cnt = 1;
                child_tp[0] = MUL_OP;
                reduce(MULTIPLY_OPERATOR, child_tp_cnt, child_tp);
                fprintf(fout, "relationop -> *\n");
                ;}
    break;

  case 61:
#line 491 "parse.y"
    {
                shift(DIV_OP, "*", 0);
                child_tp_cnt = 1;
                child_tp[0] = DIV_OP;
                reduce(MULTIPLY_OPERATOR, child_tp_cnt, child_tp);
                fprintf(fout, "relationop -> /\n");
                ;}
    break;

  case 62:
#line 500 "parse.y"
    {
                    shift(EQ_OP, "=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = EQ_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> =\n");
                    ;}
    break;

  case 63:
#line 507 "parse.y"
    {
                    shift(UEQ_OP, "#", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = UEQ_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> #\n");
                    ;}
    break;

  case 64:
#line 514 "parse.y"
    {
                    shift(LE_OP, "=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = LE_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> <\n");
                    ;}
    break;

  case 65:
#line 521 "parse.y"
    {
                    shift(GE_OP, "=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = GE_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> >\n");
                    ;}
    break;

  case 66:
#line 528 "parse.y"
    {
                    shift(GEQ_OP, ">=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = GEQ_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> >=\n");
                    ;}
    break;

  case 67:
#line 535 "parse.y"
    {
                    shift(LEQ_OP, "<=", 0);
                    child_tp_cnt = 1;
                    child_tp[0] = LEQ_OP;
                    reduce(RELATION_OPERATOR, child_tp_cnt, child_tp);
                    fprintf(fout, "relationop -> <=\n");
                    ;}
    break;

  case 68:
#line 544 "parse.y"
    {shift(WHILE_KEY,"while",0);;}
    break;

  case 69:
#line 546 "parse.y"
    {shift(DO_KEY,"do",0);;}
    break;

  case 70:
#line 547 "parse.y"
    {
                        child_tp_cnt = 4;
                        child_tp[0] = WHILE_KEY;
                        child_tp[1] = CONDITION;
                        child_tp[2] = DO_KEY;
                        child_tp[3] = SENTENCE;
                        reduce(WHILELOOP, child_tp_cnt, child_tp);
                        fprintf(fout, "whileLoop -> WHILE condition DO sentence\n");
                        ;}
    break;

  case 71:
#line 558 "parse.y"
    {shift(FOR_KEY,"for",0);;}
    break;

  case 72:
#line 560 "parse.y"
    {shift(TO_KEY,"to",0);;}
    break;

  case 73:
#line 562 "parse.y"
    {shift(DO_KEY,"do",0);;}
    break;

  case 74:
#line 563 "parse.y"
    {
                        child_tp_cnt = 6;
                        child_tp[0] = FOR_KEY;
                        child_tp[1] = ASSIGNMENT;
                        child_tp[2] = TO_KEY;
                        child_tp[3] = CONDITION;
                        child_tp[4] = DO_KEY;
                        child_tp[5] = SENTENCE;
                        reduce(FORLOOP, child_tp_cnt, child_tp);
                        fprintf(fout, "forLoop -> FOR assignment TO condition DO sentence\n");
                        ;}
    break;

  case 75:
#line 577 "parse.y"
    {
                        shift(CALL_KEY,(yyvsp[(1) - (2)].str),0);
                        shift(IDENTI, (yyvsp[(2) - (2)].str), 0);
                        child_tp_cnt = 2;
                        child_tp[0] = CALL_KEY;
                        child_tp[1] = IDENTI;
                        reduce(PROCEDURE_CALL, child_tp_cnt, child_tp);
                        fprintf(fout, "procedureCall -> CALL ID\n");
                        ;}
    break;

  case 76:
#line 588 "parse.y"
    {shift(READ_KEY, "read", 0);;}
    break;

  case 77:
#line 589 "parse.y"
    {shift(LEFTPARAN, "(", 0);;}
    break;

  case 78:
#line 590 "parse.y"
    {
                            shift(RIGHTPARAN, ")", 0);
                            child_tp_cnt = 4;
                            child_tp[0] = READ_KEY;
                            child_tp[1] = LEFTPARAN;
                            child_tp[2] = READ_PARAMETER;
                            child_tp[3] = RIGHTPARAN;
                            reduce(READ_SENTENCE, child_tp_cnt, child_tp);
                            fprintf(fout, "readSent -> READ ( readpara )\n");
                            ;}
    break;

  case 79:
#line 602 "parse.y"
    {
                                shift(IDENTI, (yyvsp[(1) - (1)].str), 0);
                                child_tp_cnt = 1;
                                child_tp[0] = IDENTI;
                                reduce(READ_PARAMETER, child_tp_cnt, child_tp);
                                fprintf(fout, "readpara -> ID\n");
                                ;}
    break;

  case 80:
#line 609 "parse.y"
    {
                                shift(IDENTI, (yyvsp[(1) - (3)].str), 0);
                                shift(COMMA_OP, (yyvsp[(2) - (3)].str), 0);
                                child_tp_cnt = 3;
                                child_tp[0] = IDENTI;
                                child_tp[1] = COMMA_OP;
                                child_tp[2] = READ_PARAMETER;
                                reduce(READ_PARAMETER, child_tp_cnt, child_tp);
                                fprintf(fout, "readpara -> ID , readpara\n");
                                ;}
    break;

  case 81:
#line 621 "parse.y"
    {shift(WRITE_KEY, "write", 0);;}
    break;

  case 82:
#line 622 "parse.y"
    {shift(LEFTPARAN, "(", 0);;}
    break;

  case 83:
#line 623 "parse.y"
    {
                            shift(RIGHTPARAN, ")", 0);
                            child_tp_cnt = 4;
                            child_tp[0] = WRITE_KEY;
                            child_tp[1] = LEFTPARAN;
                            child_tp[2] = WRITE_PARAMETER;
                            child_tp[3] = RIGHTPARAN;
                            reduce(WRITE_SENTENCE, child_tp_cnt, child_tp);
                            fprintf(fout, "writeSent -> WRITE ( writepara )\n");
                            ;}
    break;

  case 84:
#line 635 "parse.y"
    {
                        child_tp_cnt = 1;
                        child_tp[0] = EXPRESSION;
                        reduce(WRITE_PARAMETER, child_tp_cnt, child_tp);
                        fprintf(fout, "writepara -> expr\n");
                        ;}
    break;

  case 85:
#line 641 "parse.y"
    {shift(COMMA_OP, (yyvsp[(2) - (2)].str), 0);}
    break;

  case 86:
#line 642 "parse.y"
    {
                        child_tp_cnt = 3;
                        child_tp[0] = EXPRESSION;
                        child_tp[1] = COMMA_OP;
                        child_tp[2] = WRITE_PARAMETER;
                        reduce(WRITE_PARAMETER, child_tp_cnt, child_tp);
                        fprintf(fout, "writepara -> expr , writepara\n");
                        ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2341 "parse.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 652 "parse.y"
 

void push(Node* s){
    stack[stop] = s;
    stop++;
}

void pop(){
    stop --;
    freenode(stack[stop]);
}

void show_child(Node *p){
    if(p == NULL)return;
    if(p -> childcnt == 0){
            printf("TYPE: %d ,child : 0\n",p -> type);
    } else {
            printf("TYPE: %d ,child : %d\n",p -> type,p -> childcnt);
            for(int i = 0;i < p -> childcnt;++ i){
                    show_child(p -> child[i]);
            }
    }
}

void freenode(Node* p){
    if(p -> id != NULL){
        free(p -> id);
    }
    if(p -> childcnt != 0){
        int i;
        for(i = 0;i < p -> childcnt;++ i){
                freenode(p -> child[i]);
        }
    }
    free(p);
}

void print_node(Node* p,int k){
    if(p == NULL) return;
    int type = p -> type;

    if(type == PROGRAM)                             {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< program >\n"); }
    else if(type == SUBPROGRAM)                     {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< subprogram >\n"); }
    else if(type == CONST_INSTRUCTION)              {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< const_instruction >\n");}
    else if(type == CONST_DECLARATION)              {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< const_declaration >\n");}
    else if(type == VARIABLE_INSTRUCTION)           {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< variable_instruction >\n");}
    else if(type == VARIABLE_INSTRUCTIONSUF)        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< variable_instructionsuf >\n"); }
    else if(type == PROCEDURE_HEADER)               {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< procedure_header >\n");}
    else if(type == PROCEDURE_INSTRUCTION)          {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< procedure_instruction >\n");}
    else if(type == SENTENCE)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< sentence >\n");}
    else if(type == UNEMPTY_SENTENCE)               {k--;}
    else if(type == EMPTY_SENTENCE)                 {k--;}
    else if(type == ASSIGNMENT)                     {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< assignment_sentence > \n");}
    else if(type == EXPRESSION)                     {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< expression >\n");}
    else if(type == ITEM)                           {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< item >\n");}
    else if(type == ITEM_SUF)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< item_suf >\n");}
    else if(type == FACTOR)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< factor >\n");}
    else if(type == FACTOR_SUFFIX)                  {k--;}
    else if(type == PLUS_OPERATOR)                  {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< plus_operator > \n");}
    else if(type == MULTIPLY_OPERATOR)              {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< multi_operator > \n");}
    else if(type == MULTI_SENTENCE)                 {k--;}
    else if(type == COMPOUND)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< compound_sentence >\n");}
    else if(type == RELATION_OPERATOR)              {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< relation_operator > \n");}
    else if(type == CONDITION)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< condition >\n");}
    else if(type == CONDITIONAL)                    {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< condition_sentence >\n");}
    else if(type == WHILELOOP)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< while_loop_sentence >\n");}
    else if(type == FORLOOP)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< for_loop_sentence >\n");}
    else if(type == PROCEDURE_CALL)                 {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< call_procedure >\n");}
    else if(type == READ_PARAMETER)                 {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< read_parameter > \n");}
    else if(type == READ_SENTENCE)                  {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< read_sentence >\n");}
    else if(type == WRITE_PARAMETER)                {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< write_parameter >\n");}
    else if(type == WRITE_SENTENCE)                 {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< write_sentence >\n");}
    
    
    else if(type == IDENTI)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< ID: %s >\n",p -> id);}
    else if(type == NUMBER)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< NUMBER: %d >\n",p -> value);}
    
    else if(type == CONST_KEY)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< CONST: const >\n");}
    else if(type == VAR_KEY)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< VAR: var >\n"); }
    else if(type == PROCEDURE_KEY)                  {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< PROCEDURE: procedure >\n");}
    else if(type == CALL_KEY)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< CALL: call >\n");}
    else if(type == BEGIN_KEY)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< BEGIN: begin >\n");}
    else if(type == END_KEY)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< END: end >\n");}
    else if(type == IF_KEY)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< IF: if >\n");}
    else if(type == THEN_KEY)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< THEN: then >\n");}
    else if(type == WHILE_KEY)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< WHILE: while >\n");}
    else if(type == DO_KEY)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< DO: do >\n");}
    else if(type == FOR_KEY)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< FOR: for >\n");}
    else if(type == TO_KEY)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< TO: to >\n");}
    else if(type == READ_KEY)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< READ: read >\n");}
    else if(type == WRITE_KEY)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< WRITE: write >\n");}
    else if(type == ODD_KEY)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< ODD: odd >\n");}

    else if(type == EQ_OP)                          {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< EQ_OP: = > \n");}
    else if(type == UEQ_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< UEQ_OP: # >\n");}
    else if(type == LE_OP)                          {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< LE_OP: < >\n");}
    else if(type == GE_OP)                          {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< GE_OP: > >\n");}
    else if(type == LEQ_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< LEQ_OP: <= >\n");}
    else if(type == GEQ_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< GEQ_OP: >= >\n");}
    else if(type == PLUS_OP)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< PLUS_OP: + >\n");}
    else if(type == MINUS_OP)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< MINUS_OP: - >\n");}
    else if(type == MUL_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< MUL_OP: * >\n");}
    else if(type == DIV_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< DIV_OP: / >\n");}
    else if(type == SEMI_OP)                        {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< SEMI_OP: ; >\n");}
    else if(type == ASSIGN_OP)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< ASSIGN_OP: := >\n");}
    else if(type == EOP_OP)                         {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< EOP_OP: . >\n");}
    else if(type == COMMA_OP)                       {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< COMMA_OP: , >\n");}
    else if(type == LEFTPARAN)                      {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< LEFTPARAN: ( >\n");}
    else if(type == RIGHTPARAN)                     {for(int i = 0;i < k;++ i)fprintf(fout,"  ");fprintf(fout,"< RIGHTPARAN: ) >\n");}
    

    int childno = p -> childcnt;
    for(int i = childno - 1;i >= 0; -- i){
            print_node(p -> child[i],k+1);
    }
}

int empty(){
    return stop == 0 ? 1 : 0;   
}

Node* top(){
    return stack[stop-1];
}

int inarray(int tp, int tpcnt, int tparray[TYPE_MAXN]){
    int i;
    for( i = 0;i < tpcnt;++ i){
        if(tp == tparray[i]){
            return 1;
        }
    }
    return 0;
}

void shift(int type,char* id,int number){
    Node* a;
    a = (Node*)malloc(sizeof(Node));
    a->value = number;
    a->type = type;
    if(id == NULL) {
        a->id = NULL;
    } else {
            a->id = (char*)malloc(ID_MAX_SIZE);
            strcpy(a->id, id);
    }
    a->child = NULL;
    a -> childcnt = 0;
    push(a);
}

void reduce(int type,int child_type_cnt,int child_type[TYPE_MAXN]){
    Node* father;
    father = (Node*)malloc(sizeof(Node));
    father -> value = 0;
    father -> id = NULL;
    father -> type = type;

    int cnt = 0;
    int tmptop = stop;
    fflush(stdout);

    while(tmptop > 0 && inarray(stack[tmptop-1]->type, child_type_cnt, child_type) == 1){
        tmptop --;
        cnt ++;
    }
    father -> child = (Node**)malloc(cnt * sizeof(Node*));
    int idx = 0;

    while(!empty() && inarray(top() -> type, child_type_cnt, child_type) == 1 ){
        father -> child[idx] = (Node*)malloc(sizeof(Node));
        node_copy(father -> child[idx], stack[stop-1]);
        pop();
        idx ++;
    }
    father -> childcnt = idx;
    push(father);
}

void node_copy(Node* copy,Node* copied){
    copy -> value = copied -> value;
    copy -> type = copied -> type;
    if(copied -> id == NULL) {
        copy-> id = NULL;
    }
    else {
        copy -> id = (char*)malloc(ID_MAX_SIZE);
        strcpy(copy -> id,copied -> id);
    }
    copy -> childcnt = copied -> childcnt;
    if(copy->childcnt != 0){
        copy -> child = (Node**)malloc(copy->childcnt * sizeof(Node*));
        int i;
        for( i = 0;i < copy-> childcnt;++ i){
                copy -> child[i] = (Node*)malloc(sizeof(Node));
                node_copy(copy->child[i],copied->child[i]);
        }
    }
}

 
int yywrap()
{
    return 1;
} 

int main()
{
    
    printf("Please enter files name:\n");
	scanf("%s", infile);
    outfile = "result.txt";
    
    fin = fopen(infile, "r");
	if(fin == NULL){
		printf("Cannot open the in file \n");
		return 0;
	}
	fout = fopen(outfile, "w");
	if(fout == NULL){
		printf("Cannot open the out file \n");
		return 0;
	}
    yyin = fin;
    
    yyparse();
    printf("stop = %d\n",stop);
    fprintf(fout, "\n\n\n******************** tree ********************\n");
    print_node(top(),0);
    if(stop == 1){
        freenode(top());
    }

    fclose(fout);
	printf("Finish!\n");
    return 0;
}

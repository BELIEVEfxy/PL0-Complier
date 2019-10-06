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
     ENDD = 0,
     IF = 258,
     THEN = 259,
     WHILE = 260,
     DO = 261,
     READ = 262,
     WRITE = 263,
     CALL = 264,
     BEGINN = 265,
     END = 266,
     CONST = 267,
     VAR = 268,
     PROCEDURE = 269,
     ODD = 270,
     FOR = 271,
     TO = 272,
     DOWNTO = 273,
     IDENTIFIER = 274,
     NUMBER = 275,
     ASSIGNMENT = 276
   };
#endif
/* Tokens.  */
#define ENDD 0
#define IF 258
#define THEN 259
#define WHILE 260
#define DO 261
#define READ 262
#define WRITE 263
#define CALL 264
#define BEGINN 265
#define END 266
#define CONST 267
#define VAR 268
#define PROCEDURE 269
#define ODD 270
#define FOR 271
#define TO 272
#define DOWNTO 273
#define IDENTIFIER 274
#define NUMBER 275
#define ASSIGNMENT 276




/* Copy the first part of user declarations.  */
#line 1 "parse.y"

//display栈、符号表栈、代码地址栈、循环栈、程序栈
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userdef.h"
#define stack_size 128

char infile[32];
char *outfile;
FILE *fin;
FILE *fout;
extern FILE * yyin;
extern FILE * yyout;

int code_line=1;                                                    /*记录代码行数*/
extern varIndex strMem[256];
int error_cnt = 0;

int iMaxIndex=0;  
int iCurIndex=0;  
int yylex(void);
void yyerror(char *);

FILE *CodeOutput;                                                   /*code输出文件指针*/
int total_line=0;                                                   /*pcode总的行数*/
int cur_layer = 1;                                                  /*现在的层数*/
int code_address_stack[stack_size];                                 /*记录代码地址的栈*/
int code_address_stack_point=0;                                     /*代码地址栈顶*/
int loop_stack[stack_size];                                         /*用于循环的栈*/
int loop_stack_point = 0;                                           /*循环栈顶*/

struct code_struct *mycode;                                         /*存储翻译之后的代码*/
struct sign *sign_stack;                                            /*标志（符号）栈*/
int sign_top = 0;                                                   /*标志栈顶*/

int display_stack[stack_size];                                      /*display栈*/
int display_top = 0;                                                /*display的栈顶*/

struct procedure_pos * procedure_position;                          /*过程位置*/
int pro_ct = 0;                                                     /*记录过程的个数*/
int procedure_stack[stack_size];                                            /*过程栈*/
int procedure_stack_point = 0;                                      /*过程栈顶*/
int cur_pro_ct=0;                                                   /*现在过程的代号*/

void PushProcedurePosition(char *c,int p);                          /*将程序的位置记录在procedure_position中*/
int FindProcedurePosition(char *s);                                 /*找到过程位置*/
int CheckSignIsDeclare(char *tag_name);                             /*看定义的标识符之前有没有定义过*/
int FindSign(char *tag_name);                                       /*找sign是否存在*/
void PopSignStack();                                                /*将所有的sign退栈，并且display中最上面的程序也需要退出来*/
void PushSignStack(char *s,int t);                                  /*将s加入sign栈中*/
void AddPcode(int thef, int thel, int thea);                        /*添加类PCODE代码*/
void ChangePcode(int theline, int thef, int thel, int thea);        /*将第theline行代码改为所指的*/
int CaculateA(int pos_flag);                                        /*计算偏移量a*/
void PrintPcode(struct code_struct ToPrint);                        /*按照类PCODE输出代码*/
int cmp(const void *a ,const void *b);                              /*排序函数*/



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
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 209 "parse.tab.c"

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   111

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNRULES -- Number of states.  */
#define YYNSTATES  136

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    27,     2,     2,     2,     2,
      32,    33,    30,    28,    36,    29,    34,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
      25,    26,    24,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     9,    10,    16,    20,    21,    25,
      26,    33,    34,    40,    41,    42,    47,    48,    49,    55,
      56,    60,    62,    64,    66,    68,    70,    72,    74,    76,
      77,    78,    83,    87,    89,    93,    97,   100,   101,   107,
     108,   109,   116,   119,   120,   121,   132,   133,   134,   145,
     147,   148,   153,   155,   156,   161,   166,   171,   172,   173,
     179,   182,   185,   187,   189,   193,   194,   199,   200,   203,
     204,   206,   208,   210,   212,   214,   216,   218,   220,   222
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      38,     0,    -1,    -1,    39,    40,    34,     0,    -1,    -1,
      42,    45,    49,    41,    52,    -1,    12,    43,    35,    -1,
      -1,    19,    26,    20,    -1,    -1,    19,    26,    20,    44,
      36,    43,    -1,    -1,    13,    19,    46,    47,    35,    -1,
      -1,    -1,    36,    19,    48,    47,    -1,    -1,    -1,    51,
      40,    35,    50,    49,    -1,    -1,    14,    19,    35,    -1,
      53,    -1,    56,    -1,    58,    -1,    60,    -1,    63,    -1,
      73,    -1,    74,    -1,    64,    -1,    -1,    -1,    19,    54,
      21,    75,    -1,    52,    35,    55,    -1,    52,    -1,    10,
      55,    11,    -1,    75,    85,    75,    -1,    15,    75,    -1,
      -1,     3,    57,    59,     4,    52,    -1,    -1,    -1,     5,
      61,    57,    62,     6,    52,    -1,     9,    19,    -1,    -1,
      -1,    16,    19,    21,    20,    65,    17,    20,    66,     6,
      52,    -1,    -1,    -1,    16,    19,    21,    20,    67,    18,
      20,    68,     6,    52,    -1,    19,    -1,    -1,    19,    70,
      36,    69,    -1,    75,    -1,    -1,    75,    72,    36,    71,
      -1,     7,    32,    69,    33,    -1,     8,    32,    71,    33,
      -1,    -1,    -1,    83,    76,    78,    77,    80,    -1,    78,
      80,    -1,    79,    82,    -1,    19,    -1,    20,    -1,    32,
      75,    33,    -1,    -1,    83,    78,    81,    80,    -1,    -1,
      84,    79,    -1,    -1,    28,    -1,    29,    -1,    30,    -1,
      31,    -1,    26,    -1,    27,    -1,    25,    -1,    22,    -1,
      24,    -1,    23,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    73,    73,    73,    93,    90,   104,   105,   110,   115,
     115,   125,   124,   132,   138,   137,   145,   150,   149,   159,
     164,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     195,   195,   213,   214,   216,   221,   222,   226,   226,   240,
     244,   240,   262,   280,   294,   279,   318,   332,   317,   360,
     372,   372,   388,   392,   392,   400,   403,   408,   411,   408,
     415,   419,   424,   437,   440,   445,   444,   447,   451,   452,
     456,   457,   460,   461,   465,   466,   467,   468,   469,   470
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "IF", "THEN", "WHILE", "DO",
  "READ", "WRITE", "CALL", "BEGINN", "END", "CONST", "VAR", "PROCEDURE",
  "ODD", "FOR", "TO", "DOWNTO", "IDENTIFIER", "NUMBER", "ASSIGNMENT",
  "\"<=\"", "\">=\"", "'>'", "'<'", "'='", "'#'", "'+'", "'-'", "'*'",
  "'/'", "'('", "')'", "'.'", "';'", "','", "$accept", "program", "@1",
  "subprogram", "@2", "constInstruction", "constDeclaration", "@3",
  "variableInstruction", "@4", "variableDeclaration", "@5",
  "procedureInstruction", "@6", "procedureHeader", "sentence",
  "assignmentSentence", "@7", "multiSentence", "compoundSentence",
  "condition", "conditionSentence", "@8", "whileLoop", "@9", "@10",
  "procedureCall", "forLoop", "@11", "@12", "@13", "@14", "readPara",
  "@15", "writePara", "@16", "readSentence", "writeSentence", "expression",
  "@17", "@18", "item", "factor", "addItem", "@19", "mulItem", "plusOp",
  "mulOp", "relationOp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,    62,    60,    61,    35,    43,    45,
      42,    47,    40,    41,    46,    59,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    39,    38,    41,    40,    42,    42,    43,    44,
      43,    46,    45,    45,    48,    47,    47,    50,    49,    49,
      51,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      54,    53,    55,    55,    56,    57,    57,    59,    58,    61,
      62,    60,    63,    65,    66,    64,    67,    68,    64,    69,
      70,    69,    71,    72,    71,    73,    74,    76,    77,    75,
      75,    78,    79,    79,    79,    81,    80,    80,    82,    82,
      83,    83,    84,    84,    85,    85,    85,    85,    85,    85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     5,     3,     0,     3,     0,
       6,     0,     5,     0,     0,     4,     0,     0,     5,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       0,     4,     3,     1,     3,     3,     2,     0,     5,     0,
       0,     6,     2,     0,     0,    10,     0,     0,    10,     1,
       0,     4,     1,     0,     4,     4,     4,     0,     0,     5,
       2,     2,     1,     1,     3,     0,     4,     0,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     7,     1,     0,     0,    13,     0,     0,     0,
       0,    19,     0,     6,     3,    11,     0,     4,     7,     8,
      16,     0,    29,     0,     0,     0,     0,    20,     0,    39,
       0,     0,     0,    29,     0,    30,     5,    21,    22,    23,
      24,    25,    28,    26,    27,    17,     0,    14,    12,     0,
      62,    63,    70,    71,     0,    37,     0,    67,    69,    57,
       0,     0,     0,    42,    33,     0,     0,     0,    19,    10,
      16,    36,     0,     0,    77,    79,    78,    76,    74,    75,
       0,    60,     0,    72,    73,    61,     0,     0,    40,    49,
       0,     0,    52,    29,    34,     0,     0,    18,    15,    64,
      29,    35,    65,    68,    58,     0,     0,    55,    56,     0,
      32,    43,    31,    38,    67,    67,    29,     0,     0,     0,
       0,    66,    59,    41,    51,    54,     0,     0,    44,    47,
       0,     0,    29,    29,    45,    48
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,    22,     6,     8,    24,    11,    20,
      26,    70,    17,    68,    18,    64,    37,    67,    65,    38,
      55,    39,    73,    40,    60,   105,    41,    42,   119,   130,
     120,   131,    90,   106,    91,   109,    43,    44,    56,    87,
     115,    57,    58,    81,   114,    85,    59,    86,    80
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -69
static const yytype_int8 yypact[] =
{
     -69,    13,     3,   -69,    10,    -3,    20,    23,     1,    50,
      32,    38,    33,   -69,   -69,   -69,    35,   -69,     3,    19,
      21,    26,    18,    27,    22,    37,    28,   -69,   -12,   -69,
      34,    36,    45,    18,    46,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,    10,   -69,   -69,   -10,
     -69,   -69,   -69,   -69,   -10,   -69,    16,   -24,    14,   -69,
     -12,    48,   -10,   -69,    39,    58,    51,    52,    38,   -69,
      21,   -69,    42,    67,   -69,   -69,   -69,   -69,   -69,   -69,
     -10,   -69,    -8,   -69,   -69,   -69,    -8,    -8,   -69,    40,
      44,    47,    43,    18,   -69,    61,   -10,   -69,   -69,   -69,
      18,   -69,   -69,   -69,   -69,    76,    49,   -69,   -69,    53,
     -69,    65,   -69,   -69,   -24,   -24,    18,    48,   -10,    69,
      66,   -69,   -69,   -69,   -69,   -69,    68,    70,   -69,   -69,
      81,    85,    18,    18,   -69,   -69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   -69,    74,   -69,   -69,    54,   -69,   -69,   -69,
      25,   -69,    29,   -69,   -69,   -22,   -69,   -69,     0,   -69,
      41,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -21,   -69,   -20,   -69,   -69,   -69,   -48,   -69,
     -69,   -52,    17,   -68,   -69,   -69,   -55,   -69,   -69
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -54
static const yytype_int16 yytable[] =
{
      36,    71,    82,    49,    52,    53,    72,    50,    51,    50,
      51,    50,    51,     3,    92,     4,    52,    53,    52,    53,
      54,    28,    54,    29,    54,    30,    31,    32,    33,     7,
     102,     9,   101,    10,    34,   104,    13,    35,    74,    75,
      76,    77,    78,    79,    83,    84,   121,   122,   112,    12,
      14,    15,    16,    19,    21,    -9,    47,    25,    46,    82,
      82,    27,    45,    48,    63,    66,    61,    89,    62,    94,
      92,   100,    95,    96,    93,    99,   -50,   107,   113,   -53,
     108,   111,   116,   -46,   127,   117,   126,   132,   128,   118,
     129,   133,    23,   110,   123,    98,   124,    97,   125,     0,
      69,    88,     0,   103,     0,     0,     0,     0,     0,     0,
     134,   135
};

static const yytype_int16 yycheck[] =
{
      22,    49,    57,    15,    28,    29,    54,    19,    20,    19,
      20,    19,    20,     0,    62,    12,    28,    29,    28,    29,
      32,     3,    32,     5,    32,     7,     8,     9,    10,    19,
      82,    34,    80,    13,    16,    87,    35,    19,    22,    23,
      24,    25,    26,    27,    30,    31,   114,   115,    96,    26,
       0,    19,    14,    20,    19,    36,    19,    36,    36,   114,
     115,    35,    35,    35,    19,    19,    32,    19,    32,    11,
     118,     4,    21,    21,    35,    33,    36,    33,   100,    36,
      33,    20,     6,    18,    18,    36,    17,     6,    20,    36,
      20,     6,    18,    93,   116,    70,   117,    68,   118,    -1,
      46,    60,    -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,
     132,   133
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    39,     0,    12,    40,    42,    19,    43,    34,
      13,    45,    26,    35,     0,    19,    14,    49,    51,    20,
      46,    19,    41,    40,    44,    36,    47,    35,     3,     5,
       7,     8,     9,    10,    16,    19,    52,    53,    56,    58,
      60,    63,    64,    73,    74,    35,    36,    19,    35,    15,
      19,    20,    28,    29,    32,    57,    75,    78,    79,    83,
      61,    32,    32,    19,    52,    55,    19,    54,    50,    43,
      48,    75,    75,    59,    22,    23,    24,    25,    26,    27,
      85,    80,    83,    30,    31,    82,    84,    76,    57,    19,
      69,    71,    75,    35,    11,    21,    21,    49,    47,    33,
       4,    75,    78,    79,    78,    62,    70,    33,    33,    72,
      55,    20,    75,    52,    81,    77,     6,    36,    36,    65,
      67,    80,    80,    52,    69,    71,    17,    18,    20,    20,
      66,    68,     6,     6,    52,    52
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
#line 73 "parse.y"
    {
                    display_top++; 
                    display_stack[display_top] = 1; 
                    PushProcedurePosition("program",0); //改变procedure_position
                    cur_pro_ct = pro_ct-1; 
                    procedure_stack[procedure_stack_point] = pro_ct-1; 
                    procedure_stack_point++;
                    ;}
    break;

  case 3:
#line 82 "parse.y"
    {
                    printf("\nSuccessfully Compiled\n0 error(s) 0 warning(s)\n"); 
                    AddPcode(8,0,0);
                    ;}
    break;

  case 4:
#line 93 "parse.y"
    {
                procedure_position[cur_pro_ct].pos = total_line; //记录程序的位置
                AddPcode(5,0,3+procedure_position[cur_pro_ct].var_number);
                ;}
    break;

  case 8:
#line 110 "parse.y"
    {
                                if(CheckSignIsDeclare(strMem[(yyvsp[(1) - (3)])].sMark) == 1){
                                    PushSignStack(strMem[(yyvsp[(1) - (3)])].sMark,(yyvsp[(3) - (3)]));
                                }
                                ;}
    break;

  case 9:
#line 115 "parse.y"
    {
                                if(CheckSignIsDeclare(strMem[(yyvsp[(1) - (3)])].sMark) == 1){
                                    PushSignStack(strMem[(yyvsp[(1) - (3)])].sMark,(yyvsp[(3) - (3)]));
                                }
                                ;}
    break;

  case 11:
#line 125 "parse.y"
    {
                    if(CheckSignIsDeclare(strMem[(yyvsp[(2) - (2)])].sMark) == 1){
                        PushSignStack(strMem[(yyvsp[(2) - (2)])].sMark,-1);
                        procedure_position[cur_pro_ct].var_number++;//当前程序变量数目+1
                    } 
                    ;}
    break;

  case 14:
#line 138 "parse.y"
    {
                    if(CheckSignIsDeclare(strMem[(yyvsp[(2) - (2)])].sMark) == 1){
                        PushSignStack(strMem[(yyvsp[(2) - (2)])].sMark,-1);
                        procedure_position[cur_pro_ct].var_number++;//当前程序变量数目+1
                    } 
                    ;}
    break;

  case 17:
#line 150 "parse.y"
    {
            cur_layer--; /*程序结束后退栈*/
            procedure_stack_point--;  /*指向的是过程栈的顶，没东西，因此要--*/
            cur_pro_ct = procedure_stack[procedure_stack_point-1]; /*获得退栈后所在过程的编号，因此[]中要-1*/
            procedure_stack[procedure_stack_point] = -1; /*清空栈*/
            PopSignStack(); /*把该过程的ID清空*/
            AddPcode(8,0,0); 
            ;}
    break;

  case 20:
#line 165 "parse.y"
    {
                if(CheckSignIsDeclare(strMem[(yyvsp[(2) - (3)])].sMark) == 1){
                    PushSignStack(strMem[(yyvsp[(2) - (3)])].sMark,-2);
                    display_top++; 
                    display_stack[display_top] = sign_top+1; 
                    cur_layer++; 
                    PushProcedurePosition(strMem[(yyvsp[(2) - (3)])].sMark,total_line+1);//有pro_ct++
                    cur_pro_ct = pro_ct-1; /*在一个过程开始时，记录这个过程的编号*/
                    procedure_stack[procedure_stack_point] = pro_ct - 1; /*存下这个过程的编号，方便程序中用到procedure_position时直接访问该过程的信息*/
                    procedure_stack_point++; 
                }  
                ;}
    break;

  case 30:
#line 195 "parse.y"
    {
                    int pos_flag = FindSign(strMem[(yyvsp[(1) - (1)])].sMark); //找sign是否存在，返回在sign_stack的位置
                    if(pos_flag > 0){ 
                        if(sign_stack[pos_flag].type != -1){//-1表示为var类型的标识符
                            printf("in line %d illegal name\n",code_line); 
                            exit(1);
                        }  
                    } 
                    ;}
    break;

  case 31:
#line 205 "parse.y"
    {
                    int pos_flag = FindSign(strMem[(yyvsp[(1) - (4)])].sMark); 
                    AddPcode(3,cur_layer-sign_stack[pos_flag].layer,CaculateA(pos_flag));/*STO l a*/
                    ;}
    break;

  case 35:
#line 221 "parse.y"
    {AddPcode(8,0,(yyvsp[(2) - (3)]));;}
    break;

  case 36:
#line 222 "parse.y"
    {AddPcode(8,0,6);;}
    break;

  case 37:
#line 226 "parse.y"
    {
                        AddPcode(7,0,-1); /*JPC，条件跳转，栈顶布尔值非真跳转到地址a，条件不满足时转*/
                        code_address_stack[code_address_stack_point] = total_line-1; /*记录条件判断的位置*/
                        code_address_stack_point++;  
                        ;}
    break;

  case 38:
#line 231 "parse.y"
    {/*条件满足*/
                        code_address_stack_point--;
                        int target_line = code_address_stack[code_address_stack_point]; 
                        code_address_stack[code_address_stack_point]  = -1; 
                        ChangePcode(target_line,7,0,total_line); /*此时的total_line表示的是if语句结束后的pcode代码的位置*/
                        ;}
    break;

  case 39:
#line 240 "parse.y"
    {
                    loop_stack[loop_stack_point] = total_line; /*记录JMP回来的位置*/
                    loop_stack_point++; 
                    ;}
    break;

  case 40:
#line 244 "parse.y"
    {  
                    AddPcode(7,0,-1); /*JPC 要跳转的地址还没有，先存为-1，后面有ChangePcode()*/
                    code_address_stack[code_address_stack_point] = total_line-1; /*记录条件判断的位置，方便后面ChangePcode找到要修改的位置*/
                    code_address_stack_point++; 
                    ;}
    break;

  case 41:
#line 249 "parse.y"
    { 
                    loop_stack_point--;  
                    AddPcode(6,0,loop_stack[loop_stack_point]); /*JMP 无条件跳转至a地址*/
                    loop_stack[loop_stack_point] = -1;  
                    code_address_stack_point--; 
                    int target_line = code_address_stack[code_address_stack_point]; 
                    ChangePcode(target_line,7,0,total_line); 
                    code_address_stack[code_address_stack_point]  = -1; 
                    ;}
    break;

  case 42:
#line 262 "parse.y"
    {
                        int pos_flag = FindSign(strMem[(yyvsp[(2) - (2)])].sMark); 
                        if(pos_flag > 0){
                            if(sign_stack[pos_flag].type==-2 || sign_stack[pos_flag].type == -3){
                                int target_pos = FindProcedurePosition(strMem[(yyvsp[(2) - (2)])].sMark); /*根据procedure的名字来找位置*/
                                AddPcode(4,cur_layer-sign_stack[pos_flag].layer,target_pos); /*CAL l a 调用过程 a为调用地址，l为层差*/
                            }else{
                                printf("error in line %d illegal name\n",code_line); exit(1);
                            }      
                        }  
                        ;}
    break;

  case 43:
#line 280 "parse.y"
    {
                            int pos_flag = FindSign(strMem[(yyvsp[(2) - (4)])].sMark); /*返回ID的地址*/
                            if(pos_flag > 0){ /*ID不存在，报错*/
                                if(sign_stack[pos_flag].type == -1){} /*ID为var类型*/
                                else{
                                    printf("error in line %d illegal input\n",code_line);
                                    exit(1);
                                }
                            } 
                            AddPcode(1,0,(yyvsp[(4) - (4)]));/*LIT 0 a 把NUMBER的值取到栈顶*/
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); /*STO 0 a 把栈顶的值存到ID中*/
                            loop_stack[loop_stack_point] = total_line; /*loop_stack中存下循环入口指令的地址*/
                            loop_stack_point++; /*如果有多层循环，那么loop_stack中会有多层循环的入口地址*/
                            ;}
    break;

  case 44:
#line 294 "parse.y"
    { 
                        int pos_flag = FindSign(strMem[(yyvsp[(2) - (7)])].sMark); /*找到ID的地址*/
                        AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); /*将变量值取到栈顶*/
                        AddPcode(1,0,(yyvsp[(7) - (7)]));/*LIT*/
                        AddPcode(8,0,13);/*OPR < */
                        AddPcode(7,0,-1);/*JPC*/
                        code_address_stack[code_address_stack_point] = total_line-1; /*存着上条JPC的位置，方便后面ChangePcode修改地址，因为跳转的地址只有在循环结束后才能知道*/
                        code_address_stack_point++;  
                        ;}
    break;

  case 45:
#line 303 "parse.y"
    { 
                        int pos_flag = FindSign(strMem[(yyvsp[(2) - (10)])].sMark);   
                        AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); /*把ID的值取到栈顶*/
                        AddPcode(1,0,1);/*把常数1取到栈顶*/
                        AddPcode(8,0,2);/*模拟循环变量+1的操作*/
                        AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag));  /*将+1后的值存到循环变量里*/
                        loop_stack_point--; /*前面有++，退一层，找到本层循环的入口地址*/
                        AddPcode(6,0,loop_stack[loop_stack_point]); /*JMP 0 a 无条件跳转至a地址（循环开始的位置）*/
                        loop_stack[loop_stack_point] = -1;  /*该层循环结束，清空栈*/
                        code_address_stack_point--;   
                        int target_line = code_address_stack[code_address_stack_point];  /*找到需要修改的代码的地址*/
                        ChangePcode(target_line,7,0,total_line);   /*修改地址*/
                        code_address_stack[code_address_stack_point]  = -1;  /*清空栈*/
                        ;}
    break;

  case 46:
#line 318 "parse.y"
    {
                            int pos_flag = FindSign(strMem[(yyvsp[(2) - (4)])].sMark); 
                            if(pos_flag>0){
                                if(sign_stack[pos_flag].type == -1){} 
                                else{
                                    printf("error in line %d illegal input\n",code_line);
                                    exit(1);
                                }
                            } 
                            AddPcode(1,0,(yyvsp[(4) - (4)]));
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); 
                            loop_stack[loop_stack_point] = total_line; 
                            loop_stack_point++; 
                            ;}
    break;

  case 47:
#line 332 "parse.y"
    {  
                            int pos_flag = FindSign(strMem[(yyvsp[(2) - (7)])].sMark);  
                            AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); 
                            AddPcode(1,0,(yyvsp[(7) - (7)])); 
                            AddPcode(8,0,11);
                            AddPcode(7,0,-1);   
                            code_address_stack[code_address_stack_point] = total_line-1; 
                            code_address_stack_point++; 
                            ;}
    break;

  case 48:
#line 341 "parse.y"
    { 
                            int pos_flag = FindSign(strMem[(yyvsp[(2) - (10)])].sMark);   
                            AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag));   
                            AddPcode(1,0,1);AddPcode(8,0,3); 
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag)); 
                            loop_stack_point--; 
                            AddPcode(6,0,loop_stack[loop_stack_point]); 
                            loop_stack[loop_stack_point] = -1;  
                            code_address_stack_point--;  
                            int target_line = code_address_stack[code_address_stack_point]; 
                            ChangePcode(target_line,7,0,total_line);  
                            code_address_stack[code_address_stack_point]  = -1; 
                            ;}
    break;

  case 49:
#line 360 "parse.y"
    {
                    int pos_flag = FindSign(strMem[(yyvsp[(1) - (1)])].sMark);  
                    if(pos_flag>0){
                        if(sign_stack[pos_flag].type == -1){
                            AddPcode(8,0,16); /*从命令行读入一个并放入栈顶*/
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer,CaculateA(pos_flag));/*栈顶的值放入变量ID中*/
                        } else {
                            printf("error in line  %d  change a const parameter\n",code_line); 
                            exit(1);
                        }    
                    } 
                    ;}
    break;

  case 50:
#line 372 "parse.y"
    {
                    int pos_flag = FindSign(strMem[(yyvsp[(1) - (1)])].sMark);  
                    if(pos_flag>0){
                        if(sign_stack[pos_flag].type == -1){
                            AddPcode(8,0,16); /*从命令行读入一个并放入栈顶*/
                            AddPcode(3,cur_layer-sign_stack[pos_flag].layer,CaculateA(pos_flag));/*栈顶的值放入变量ID中*/
                        } else {
                            printf("error in line  %d  change a const parameter\n",code_line); 
                            exit(1);
                        }    
                    } 
                    ;}
    break;

  case 52:
#line 388 "parse.y"
    {
                    AddPcode(8,0,14);
                    AddPcode(8,0,15);
                    ;}
    break;

  case 53:
#line 392 "parse.y"
    {
                    AddPcode(8,0,14);
                    AddPcode(8,0,15);
                    ;}
    break;

  case 57:
#line 408 "parse.y"
    {
                AddPcode(1,0,0);
                ;}
    break;

  case 58:
#line 411 "parse.y"
    {
                AddPcode(8,0,(yyvsp[(1) - (3)]));
                ;}
    break;

  case 62:
#line 424 "parse.y"
    {
                    int pos_flag = FindSign(strMem[(yyvsp[(1) - (1)])].sMark); 
                    if(pos_flag > 0) {
                        if(sign_stack[pos_flag].type == -1){
                            AddPcode(2,cur_layer-sign_stack[pos_flag].layer, CaculateA(pos_flag));  /*LOD var*/
                        } else if(sign_stack[pos_flag].type>=0){
                            AddPcode(1,0,sign_stack[pos_flag].type);/*LIT const*/
                        } else{
                            printf("error in line: %d  illegal name\n",code_line);
                            exit(1);
                        } 
                    }  
                    ;}
    break;

  case 63:
#line 437 "parse.y"
    {
                        AddPcode(1,0,(yyvsp[(1) - (1)])); 
                        ;}
    break;

  case 65:
#line 445 "parse.y"
    {AddPcode(8,0,(yyvsp[(1) - (2)]));;}
    break;

  case 68:
#line 451 "parse.y"
    {AddPcode(8,0,(yyvsp[(1) - (2)]));;}
    break;

  case 70:
#line 456 "parse.y"
    {(yyval) = 2; ;}
    break;

  case 71:
#line 457 "parse.y"
    {(yyval) = 3; ;}
    break;

  case 72:
#line 460 "parse.y"
    {(yyval) = 4; ;}
    break;

  case 73:
#line 461 "parse.y"
    {(yyval) = 5; ;}
    break;

  case 74:
#line 465 "parse.y"
    {(yyval) = 8; ;}
    break;

  case 75:
#line 466 "parse.y"
    {(yyval) = 9; ;}
    break;

  case 76:
#line 467 "parse.y"
    {(yyval) = 10; ;}
    break;

  case 77:
#line 468 "parse.y"
    {(yyval) = 13; ;}
    break;

  case 78:
#line 469 "parse.y"
    {(yyval) = 12; ;}
    break;

  case 79:
#line 470 "parse.y"
    {(yyval) = 11; ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1956 "parse.tab.c"
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


#line 473 "parse.y"

/*将程序的位置记录在procedure_position中*/
void PushProcedurePosition(char *c,int p){ 
    for(int i = 0; i < 11; ++i){
        procedure_position[pro_ct].name[i] = '\0';
    }
    strcpy(procedure_position[pro_ct].name, c);  
    procedure_position[pro_ct].pos = p;
    procedure_position[pro_ct].var_number = 0;
    pro_ct ++;  //程序个数加一
}
/*看定义的标识符之前有没有定义过*/
int CheckSignIsDeclare(char *tag_name){  
    int bias = display_stack[display_top];  //栈顶偏差
    while(bias <= sign_top){
        if(strcmp(tag_name,sign_stack[bias].name) == 0){  //定义过，返回错误
            printf("error!!! line %d: declare repeatedly \n",code_line);
            exit(1);
        }
        if(sign_stack[bias].previous == 0){
            break;
        }
        bias ++;
    }
    return 1;
}
/*找sign是否存在*/
int FindSign(char *tag_name){  
    int display_bias = display_top;
    int cur_bias;
    while(display_bias > 0){
        cur_bias = display_stack[display_bias];
        while(cur_bias <= sign_top){
            if(strcmp(tag_name,sign_stack[cur_bias].name) == 0){//find
                return cur_bias;
            }
            if(sign_stack[cur_bias].previous==0){  //代表找到这个程序的底部
                break;
            }
            cur_bias++;
        }
        display_bias --;
    }
    printf("error!!! line %d: no such parameter \n",code_line);  //没找到
    exit(1);
}
/*将该过程的所有的sign退栈，并且display中最上面的程序也需要退出来*/
void PopSignStack(){  
    
    int bias = display_stack[display_top]-1;
    
    for(int i=sign_top; i>bias;--i){  //退sign
        sign_stack[i].type = -10;
        sign_stack[i].layer = -1;
        sign_stack[i].previous = -1;
        for(int j=0;j<11;++j){
            sign_stack[i].name[j] = '\0';
        }
    }
    sign_top = bias;
    sign_stack[sign_top].previous = 0;
    
    sign_stack[sign_top].type = -3;
    display_stack[display_top] = 0;  //退display
    display_top--;
}
/*将s加入sign 栈中*/
void PushSignStack(char *s,int t){ 
    sign_top++;
    for(int i=0;i<11;++i){
        sign_stack[sign_top].name[i] = '\0';
    }
    strcpy(sign_stack[sign_top].name,s);
    sign_stack[sign_top].type = t;
    sign_stack[sign_top].layer = cur_layer;
    sign_stack[sign_top].previous = 0;
    if(sign_top > 1){  //按照实际情况更新previous的值
        int pre_bias = sign_top-1;
        if(sign_stack[pre_bias].type > -2){
            sign_stack[pre_bias].previous = sign_top;
        }
        else if(sign_stack[pre_bias].type == -3){
            sign_stack[pre_bias].previous = sign_top;
        }
    }
}
/*添加类PCODE代码*/
void AddPcode(int thef, int thel, int thea){  
    mycode[total_line].line = total_line;
    mycode[total_line].f = thef;
    mycode[total_line].l = thel;
    mycode[total_line].a = thea;
    total_line++;
    
}
/*将第theline行代码改为所指的*/
void ChangePcode(int theline, int thef, int thel, int thea){   
    mycode[theline].f = thef;
    mycode[theline].l = thel;
    mycode[theline].a = thea;
}
/*计算偏移量*/
int CaculateA(int pos_flag){  
    int target_flag = pos_flag;
    
    if(pos_flag >= 1){
        while(target_flag >= 1){
            if(sign_stack[target_flag].type <= -2 || sign_stack[target_flag].type >= 0){
                return pos_flag-target_flag + 2;
            }
            target_flag--;
        }
        return pos_flag+2;
    }
    else{  //不正确
        printf("error\n");
        exit(1);
    }
}
/*找到过程位置*/
int FindProcedurePosition(char *s){   
    
    for(int i=cur_pro_ct; i<pro_ct; ++i){
        if(strcmp(procedure_position[i].name,s) == 0){
            
            return procedure_position[i].pos;
        }
    }
    printf("error in func FindProcedurePosition\n");  //找不到
    exit(1);
}
/*按照类PCODE输出代码*/
void PrintPcode(struct code_struct ToPrint){   
    int thef = ToPrint.f;
    fprintf(CodeOutput,"(%d)\t", ToPrint.line);
    switch(thef){
        case 1:fprintf(CodeOutput,"LIT\t");break;
        case 2:fprintf(CodeOutput,"LOD\t");break;
        case 3:fprintf(CodeOutput,"STO\t");break;
        case 4:fprintf(CodeOutput,"CAL\t");break;
        case 5:fprintf(CodeOutput,"INT\t");break;
        case 6:fprintf(CodeOutput,"JMP\t");break;
        case 7:fprintf(CodeOutput,"JPC\t");break;
        case 8:fprintf(CodeOutput,"OPR\t");break;
        default:fprintf(CodeOutput,"error");exit(1);
    }
    fprintf(CodeOutput,"%d\t",ToPrint.l);
    fprintf(CodeOutput,"%d\n",ToPrint.a);
}

/*排序函数*/
int cmp(const void *a ,const void *b){   
    return (*(struct code_struct *)a).line > (*(struct code_struct *)b).line ? 1:-1;
}


int main(void) {

    printf("Please enter files name:\n");
	scanf("%s", infile);
    
    fin = fopen(infile, "r");
	if(fin == NULL){
		printf("Cannot open the in file \n");
		return 0;
	}

    CodeOutput = fopen("pcode.txt","w");  //类PCODE存放文件
    mycode = (struct code_struct*)malloc(sizeof(struct code_struct)* 2000);
    sign_stack = (struct sign*)malloc(sizeof(struct sign) * 100);
    procedure_position = (struct procedure_pos*)malloc(sizeof(struct procedure_pos) * 30);
    
    /*初始化*/
    for(int i = 0; i < stack_size; ++i){   
        procedure_stack[i] = -1;
        loop_stack[i] = -1;
        code_address_stack[i] = -1;
    }
   
    yyin = fin;
    yyparse();
    /*含有跳转的指令，都要加上现有过程的数量，即加上前面JMP指令的数量*/
    int code_bias = pro_ct;  
    for(int i = 0; i < total_line; ++i){
        //printf("%d\n",ycode[i].f);
        mycode[i].line += code_bias;
        if(mycode[i].f == 4 ||mycode[i].f == 6 || mycode[i].f == 7 ){
            mycode[i].a += code_bias;
        }
    }

    for(int i = 0; i < pro_ct; ++i){
        procedure_position[i].pos += code_bias;
    }
    /*补上前面的JMP*/
    for(int i = 0; i < pro_ct; ++i){
        mycode[total_line].line = i;
        mycode[total_line].f = 6;
        mycode[total_line].l = 0;
        mycode[total_line].a = procedure_position[i].pos;
        total_line++;
    }

    qsort(mycode,total_line,sizeof(mycode[0]),cmp);  //对代码按照行标号排序


    printf("\n");
    for(int i = 0; i < total_line; ++i){  //输出类PCODE
        PrintPcode(mycode[i]);
    }
    FILE *num_file;
    num_file = fopen("number.txt","w");  //在number文件中写下总的行数
    fprintf(num_file,"%d",total_line);

 
    return 0;
}
int yywrap(){
    return 1;
}
void yyerror(char *s) {
    printf("error in line %d %s\n",code_line-1, s);
    exit(1);
}



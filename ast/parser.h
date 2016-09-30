/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_MINIMAL_PARSER_H_INCLUDED
# define YY_MINIMAL_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int minimal_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CHUCK = 259,
    COMMA = 260,
    ASSIGN = 261,
    DIVIDE = 262,
    TIMES = 263,
    PERCENT = 264,
    L_HACK = 265,
    R_HACK = 266,
    LPAREN = 267,
    RPAREN = 268,
    LBRACK = 269,
    RBRACK = 270,
    LBRACE = 271,
    RBRACE = 272,
    PLUSCHUCK = 273,
    MINUSCHUCK = 274,
    TIMESCHUCK = 275,
    DIVIDECHUCK = 276,
    MODULOCHUCK = 277,
    ATCHUCK = 278,
    UNCHUCK = 279,
    TRIG = 280,
    UNTRIG = 281,
    PERCENTPAREN = 282,
    SHARPPAREN = 283,
    PROTECTED = 284,
    ABSTRACT = 285,
    ATSYM = 286,
    FUNCTION = 287,
    DOLLAR = 288,
    TILDA = 289,
    QUESTION = 290,
    COLON = 291,
    EXCLAMATION = 292,
    IF = 293,
    ELSE = 294,
    WHILE = 295,
    DO = 296,
    UNTIL = 297,
    LOOP = 298,
    FOR = 299,
    GOTO = 300,
    SWITCH = 301,
    CASE = 302,
    ENUM = 303,
    RETURN = 304,
    BREAK = 305,
    CONTINUE = 306,
    PLUSPLUS = 307,
    MINUSMINUS = 308,
    NEW = 309,
    SPORK = 310,
    SIZEOF = 311,
    TYPEOF = 312,
    CLASS = 313,
    INTERFACE = 314,
    STATIC = 315,
    PRIVATE = 316,
    PUBLIC = 317,
    EXTENDS = 318,
    IMPLEMENTS = 319,
    DOT = 320,
    COLONCOLON = 321,
    AND = 322,
    EQ = 323,
    GE = 324,
    GT = 325,
    LE = 326,
    LT = 327,
    MINUS = 328,
    PLUS = 329,
    NEQ = 330,
    SHIFT_LEFT = 331,
    SHIFT_RIGHT = 332,
    S_AND = 333,
    S_OR = 334,
    S_XOR = 335,
    OR = 336,
    DTOR = 337,
    OPERATOR = 338,
    FUNC_PTR = 339,
    RSL = 340,
    RSR = 341,
    RSAND = 342,
    RSOR = 343,
    RSXOR = 344,
    RAND = 345,
    ROR = 346,
    REQ = 347,
    RNEQ = 348,
    RGT = 349,
    RGE = 350,
    RLT = 351,
    RLE = 352,
    RINC = 353,
    RDEC = 354,
    RUNINC = 355,
    RUNDEC = 356,
    TEMPLATE = 357,
    NOELSE = 358,
    ARROW_LEFT = 359,
    ARROW_RIGHT = 360,
    LTB = 361,
    GTB = 362,
    VARARG = 363,
    UNION = 364,
    NUM = 365,
    FLOAT = 366,
    ID = 367,
    STRING_LIT = 368,
    CHAR_LIT = 369,
    DOC = 370
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 57 "gwion.y" /* yacc.c:1909  */

	char* sval;
	int ival;
	double fval;
  Complex* c_val;
  Polar* polar;
  Array_Sub array_sub;
  Var_Decl var_decl;
  Var_Decl_List var_decl_list;
  Type_Decl* type_decl;
  Expression   exp;
  Func_Ptr* func_ptr;
  Stmt* stmt;
  Stmt_List stmt_list;
  Arg_List arg_list;
  Decl_List decl_list; // for union
  Union* union_stmt; // for union
  Func_Def func_def;
  Section* section;
  ID_List id_list;
  Type_List type_list; // call template
  Class_Body class_body;
  Class_Ext class_ext;
  Class_Ext iface_ext;
  Class_Def class_def;
  Ast ast;

#line 198 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int minimal_parse (MyArg* arg);

#endif /* !YY_MINIMAL_PARSER_H_INCLUDED  */

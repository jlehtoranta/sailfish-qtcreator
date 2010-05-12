/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef CPLUSPLUS_RESOLVEEXPRESSION_H
#define CPLUSPLUS_RESOLVEEXPRESSION_H

#include "LookupContext.h"

#include <ASTVisitor.h>
#include <Semantic.h>
#include <FullySpecifiedType.h>

namespace CPlusPlus {

class CPLUSPLUS_EXPORT ResolveExpression: protected ASTVisitor
{
public:
    ResolveExpression(const LookupContext &context);
    virtual ~ResolveExpression();

    QList<LookupItem> operator()(ExpressionAST *ast, Scope *scope);
    QList<LookupItem> resolve(ExpressionAST *ast, Scope *scope);

    QList<LookupItem> resolveMemberExpression(const QList<LookupItem> &baseResults,
                                              unsigned accessOp,
                                              const Name *memberName,
                                              bool *replacedDotOperator = 0) const;

    QList<LookupItem> resolveBaseExpression(const QList<LookupItem> &baseResults,
                                            int accessOp,
                                            bool *replacedDotOperator = 0) const;

protected:
    QList<LookupItem> resolve(ExpressionAST *ast);

    Q_DECL_DEPRECATED QList<LookupItem> resolveMember(const Name *memberName, Class *klass,
                                                      const Name *className = 0) const;

    Q_DECL_DEPRECATED QList<LookupItem> resolveMember(const Name *memberName, ObjCClass *klass) const;

    QList<LookupItem> switchResults(const QList<LookupItem> &symbols);
    FullySpecifiedType instantiate(const Name *className, Symbol *candidate) const;

    void thisObject();

    void addResult(const FullySpecifiedType &ty, Scope *scope);
    void addResults(const QList<Symbol *> &symbols);

    bool maybeValidPrototype(Function *funTy, unsigned actualArgumentCount) const;

    using ASTVisitor::visit;

    virtual bool visit(BinaryExpressionAST *ast);
    virtual bool visit(CastExpressionAST *ast);
    virtual bool visit(ConditionAST *ast);
    virtual bool visit(ConditionalExpressionAST *ast);
    virtual bool visit(CppCastExpressionAST *ast);
    virtual bool visit(DeleteExpressionAST *ast);
    virtual bool visit(ArrayInitializerAST *ast);
    virtual bool visit(NewExpressionAST *ast);
    virtual bool visit(TypeidExpressionAST *ast);
    virtual bool visit(TypenameCallExpressionAST *ast);
    virtual bool visit(TypeConstructorCallAST *ast);
    virtual bool visit(PostfixExpressionAST *ast);
    virtual bool visit(SizeofExpressionAST *ast);
    virtual bool visit(NumericLiteralAST *ast);
    virtual bool visit(BoolLiteralAST *ast);
    virtual bool visit(ThisExpressionAST *ast);
    virtual bool visit(NestedExpressionAST *ast);
    virtual bool visit(StringLiteralAST *ast);
    virtual bool visit(ThrowExpressionAST *ast);
    virtual bool visit(TypeIdAST *ast);
    virtual bool visit(UnaryExpressionAST *ast);
    virtual bool visit(CompoundLiteralAST *ast);
    virtual bool visit(CompoundExpressionAST *ast);

    //names
    virtual bool visit(QualifiedNameAST *ast);
    virtual bool visit(OperatorFunctionIdAST *ast);
    virtual bool visit(ConversionFunctionIdAST *ast);
    virtual bool visit(SimpleNameAST *ast);
    virtual bool visit(DestructorNameAST *ast);
    virtual bool visit(TemplateIdAST *ast);

    // postfix expressions
    virtual bool visit(CallAST *ast);
    virtual bool visit(ArrayAccessAST *ast);
    virtual bool visit(PostIncrDecrAST *ast);
    virtual bool visit(MemberAccessAST *ast);

    // Objective-C expressions
    virtual bool visit(ObjCMessageExpressionAST *ast);

private:
    Scope *_scope;
    LookupContext _context;
    Semantic sem;
    QList<LookupItem> _results;
    Symbol *_declSymbol;
};

} // end of namespace CPlusPlus

#endif // CPLUSPLUS_RESOLVEEXPRESSION_H

//
// TM & (c) 2017 Lucasfilm Entertainment Company Ltd. and Lucasfilm Ltd.
// All rights reserved.  See LICENSE.txt for license.
//

#ifndef MATERIALX_MATERIAL_H
#define MATERIALX_MATERIAL_H

/// @file
/// Material element subclasses

#include <MaterialXCore/Library.h>

#include <MaterialXCore/Node.h>
#include <MaterialXCore/Value.h>

namespace MaterialX
{

/// A shared pointer to a Material
using MaterialPtr = shared_ptr<class Material>;
/// A shared pointer to a const Material
using ConstMaterialPtr = shared_ptr<const class Material>;

/// A shared pointer to a ShaderRef
using ShaderRefPtr = shared_ptr<class ShaderRef>;
/// A shared pointer to a BindParam
using BindParamPtr = shared_ptr<class BindParam>;
/// A shared pointer to a BindInput
using BindInputPtr = shared_ptr<class BindInput>;
/// A shared pointer to an Override
using OverridePtr = shared_ptr<class Override>;
/// A shared pointer to a MaterialInherit
using MaterialInheritPtr = shared_ptr<class MaterialInherit>;

/// @class Material
/// A material element within a Document.
/// 
/// A Material instantiates one or more shader nodes with a specific set of
/// data bindings.
class Material : public Element
{
  public:
    Material(ElementPtr parent, const string& name) :
        Element(parent, CATEGORY, name)
    {
    }
    virtual ~Material() { }

  protected:
    using MaterialAssignPtr = shared_ptr<class MaterialAssign>;

  public:
    /// @name ShaderRef Elements
    /// @{

    /// Add a ShaderRef to the material.
    /// @param name The name of the new ShaderRef.
    ///     If no name is specified, then a unique name will automatically be
    ///     generated.
    /// @param node An optional node string, which should match the node
    ///     attribute of the NodeDef to be referenced.
    /// @return A shared pointer to the new ShaderRef.
    ShaderRefPtr addShaderRef(const string& name = EMPTY_STRING,
                              const string& node = EMPTY_STRING);

    /// Return the ShaderRef, if any, with the given name.
    ShaderRefPtr getShaderRef(const string& name) const
    {
        return getChildOfType<ShaderRef>(name);
    }

    /// Return a vector of all ShaderRef elements in the material.
    vector<ShaderRefPtr> getShaderRefs() const
    {
        return getChildrenOfType<ShaderRef>();
    }

    /// Remove the ShaderRef, if any, with the given name.
    void removeShaderRef(const string& name)
    {
        removeChildOfType<ShaderRef>(name);
    }

    /// @}
    /// @name Override Elements
    /// @{

    /// Add a Override to the material.
    /// @param name The name of the new Override.
    ///     If no name is specified, then a unique name will automatically be
    ///     generated.
    /// @return A shared pointer to the new Override.
    OverridePtr addOverride(const string& name)
    {
        return addChild<Override>(name);
    }

    /// Return the Override, if any, with the given name.
    OverridePtr getOverride(const string& name) const
    {
        return getChildOfType<Override>(name);
    }

    /// Return a vector of all Override elements in the material.
    vector<OverridePtr> getOverrides() const
    {
        return getChildrenOfType<Override>();
    }

    /// Remove the Override, if any, with the given name.
    void removeOverride(const string& name)
    {
        removeChildOfType<Override>(name);
    }

    /// Set the value of an override by its name, creating a child element
    /// to hold the override if needed.
    template<class T> OverridePtr setOverrideValue(const string& name,
                                                   const T& value,
                                                   const string& type = EMPTY_STRING);

    /// @}
    /// @name MaterialInherit Elements
    /// @{

    /// Add a MaterialInherit to the material.
    /// @param name The name of the new MaterialInherit.
    ///     If no name is specified, then a unique name will automatically be
    ///     generated.
    /// @return A shared pointer to the new MaterialInherit.
    MaterialInheritPtr addMaterialInherit(const string& name = EMPTY_STRING)
    {
        MaterialInheritPtr ptr = addChild<MaterialInherit>(name);
        return ptr;
    }

    /// Return the MaterialInherit, if any, with the given name.
    MaterialInheritPtr getMaterialInherit(const string& name) const
    {
        return getChildOfType<MaterialInherit>(name);
    }

    /// Return a vector of all MaterialInherit elements in the material.
    vector<MaterialInheritPtr> getMaterialInherits() const
    {
        return getChildrenOfType<MaterialInherit>();
    }

    /// Remove the MaterialInherit, if any, with the given name.
    void removeMaterialInherit(const string& name)
    {
        removeChildOfType<MaterialInherit>(name);
    }

    /// @}
    /// @name References
    /// @{

    /// Return all shader nodedefs referenced by shaderrefs in this material.
    vector<NodeDefPtr> getReferencedShaderDefs() const;

    /// Return all material assigns that reference this material.
    vector<MaterialAssignPtr> getReferencingMaterialAssigns() const;

    /// @}
    /// @name Material Inheritance
    /// @{

    /// Clear any existing material inheritance, and mark this material as
    /// inheriting the given material.  If the given pointer is empty, then
    /// this material is marked as not inheriting from any material.
    void setInheritsFrom(MaterialPtr mat);

    /// Return the material, if any, that this material inherits from.
    MaterialPtr getInheritsFrom() const;

    /// @}
    /// @name Validation
    /// @{

    /// Validate that the given element tree, including all descendants, is
    /// consistent with the MaterialX specification.
    bool validate(string* message = nullptr) const override;

    /// @}

  public:
    static const string CATEGORY;
};

/// @class BindParam
/// A bind parameter element within a ShaderRef.
///
/// A BindParam binds uniform data to a Parameter of a shader NodeDef within
/// the scope of a Material.
class BindParam : public ValueElement
{
  public:
    BindParam(ElementPtr parent, const string& name) :
        ValueElement(parent, CATEGORY, name)
    {
    }
    virtual ~BindParam() { }

  public:
    static const string CATEGORY;
};

/// @class BindInput
/// A bind input element within a ShaderRef.
///
/// A BindInput binds spatially-varying data to an Input of a shader NodeDef
/// within the scope of a material.
class BindInput : public ValueElement
{
  public:
    BindInput(ElementPtr parent, const string& name) :
        ValueElement(parent, CATEGORY, name)
    {
    }
    virtual ~BindInput() { }

    /// @}
    /// @name NodeGraph String
    /// @{

    /// Set the node graph string of the BindInput.
    void setNodeGraphString(const string& graph)
    {
        setAttribute(NODE_GRAPH_ATTRIBUTE, graph);
    }

    /// Return the node graph string of the BindInput.
    const string& getNodeGraphString() const
    {
        return getAttribute(NODE_GRAPH_ATTRIBUTE);
    }

    /// @}
    /// @name Output String
    /// @{

    /// Set the output string of the BindInput.
    void setOutputString(const string& output)
    {
        setAttribute(OUTPUT_ATTRIBUTE, output);
    }

    /// Return the output string of the BindInput.
    const string& getOutputString() const
    {
        return getAttribute(OUTPUT_ATTRIBUTE);
    }

    /// @}
    /// @name Connections
    /// @{

    /// Set the output to which the BindInput is connected.
    void setConnectedOutput(OutputPtr output);

    /// Return the output, if any, to which the BindInput is connected.
    OutputPtr getConnectedOutput() const;

    /// @}

  public:
    static const string CATEGORY;
    static const string NODE_GRAPH_ATTRIBUTE;
    static const string OUTPUT_ATTRIBUTE;
};

/// @class ShaderRef
/// A shader reference element within a Material.
///
/// A ShaderRef instantiates a shader NodeDef within the context of a Material.
class ShaderRef : public Element
{
  public:
    ShaderRef(ElementPtr parent, const string& name) :
        Element(parent, CATEGORY, name)
    {
    }
    virtual ~ShaderRef() { }

    /// @name Node String
    /// @{

    /// Set the node string of the ShaderRef.
    void setNode(const string& node)
    {
        setAttribute(NODE_ATTRIBUTE, node);
    }

    /// Return true if the given ShaderRef has a node string.
    bool hasNode() const
    {
        return hasAttribute(NODE_ATTRIBUTE);
    }

    /// Return the node string of the ShaderRef.
    const string& getNode() const
    {
        return getAttribute(NODE_ATTRIBUTE);
    }

    /// @}
    /// @name NodeDef String
    /// @{

    /// Set the NodeDef string for the ShaderRef.
    void setNodeDef(const string& nodeDef)
    {
        setAttribute(NODE_DEF_ATTRIBUTE, nodeDef);
    }

    /// Return true if the given ShaderRef has a NodeDef string.
    bool hasNodeDef() const
    {
        return hasAttribute(NODE_DEF_ATTRIBUTE);
    }

    /// Return the NodeDef string for the Implementation.
    const string& getNodeDef() const
    {
        return getAttribute(NODE_DEF_ATTRIBUTE);
    }

    /// @}
    /// @name BindParam Elements
    /// @{

    /// Add a BindParam to the shader reference.
    /// @param name The name of the new BindParam.
    ///     If no name is specified, then a unique name will automatically be
    ///     generated.
    /// @param type An optional type string.
    /// @return A shared pointer to the new BindParam.
    BindParamPtr addBindParam(const string& name, const string& type = DEFAULT_TYPE_STRING)
    {
        BindParamPtr child = addChild<BindParam>(name);
        child->setType(type);
        return child;
    }

    /// Return the BindParam, if any, with the given name.
    BindParamPtr getBindParam(const string& name) const
    {
        return getChildOfType<BindParam>(name);
    }

    /// Return a vector of all BindParam elements in the shader reference.
    vector<BindParamPtr> getBindParams() const
    {
        return getChildrenOfType<BindParam>();
    }

    /// Remove the BindParam, if any, with the given name.
    void removeBindParam(const string& name)
    {
        removeChildOfType<BindParam>(name);
    }

    /// @}
    /// @name BindInput Elements
    /// @{

    /// Add a BindInput to the shader reference.
    /// @param name The name of the new BindInput.
    ///     If no name is specified, then a unique name will automatically be
    ///     generated.
    /// @param type An optional type string.
    /// @return A shared pointer to the new BindInput.
    BindInputPtr addBindInput(const string& name, const string& type = DEFAULT_TYPE_STRING)
    {
        BindInputPtr child = addChild<BindInput>(name);
        child->setType(type);
        return child;
    }

    /// Return the BindInput, if any, with the given name.
    BindInputPtr getBindInput(const string& name) const
    {
        return getChildOfType<BindInput>(name);
    }

    /// Return a vector of all BindInput elements in the shader reference.
    vector<BindInputPtr> getBindInputs() const
    {
        return getChildrenOfType<BindInput>();
    }

    /// Remove the BindInput, if any, with the given name.
    void removeBindInput(const string& name)
    {
        removeChildOfType<BindInput>(name);
    }

    /// @}
    /// @name Connections
    /// @{

    /// Return the shader NodeDef, if any, that this element references.
    NodeDefPtr getReferencedShaderDef();

    /// Return the set of outputs that this element references.
    std::set<OutputPtr> getReferencedOutputs() const
    {
        std::set<OutputPtr> outputs;
        for (BindInputPtr bindInput : getBindInputs())
        {
            OutputPtr output = bindInput->getConnectedOutput();
            if (output)
            {
                outputs.insert(output);
            }
        }
        return outputs;
    }

    /// @}

  public:
    static const string CATEGORY;
    static const string NODE_ATTRIBUTE;
    static const string NODE_DEF_ATTRIBUTE;
};

/// @class Override
/// An override element within a Material.
///
/// An Override modifies the uniform value of a public Parameter or Input
/// within the scope of a Material.
class Override : public ValueElement
{
  public:
    Override(ElementPtr parent, const string& name) :
        ValueElement(parent, CATEGORY, name)
    {
    }
    virtual ~Override() { }

    /// @name Connections
    /// @{

    /// Return the element, if any, that is modified by this override.
    ConstElementPtr getReceiver() const;

    /// @}

  public:
    static const string CATEGORY;
};

/// @class MaterialInherit
/// A material inheritance element within a Material.
class MaterialInherit : public Element
{
  public:
    MaterialInherit(ElementPtr parent, const string& name) :
        Element(parent, CATEGORY, name)
    {
    }
    virtual ~MaterialInherit() { }

  public:
    static const string CATEGORY;
};

template<class T> OverridePtr Material::setOverrideValue(const string& name,
                                                         const T& value,
                                                         const string& type)
{
    OverridePtr override = getChildOfType<Override>(name);
    if (!override)
        override = addChild<Override>(name);
    override->setValue(value, type);
    return override;
}

} // namespace MaterialX

#endif

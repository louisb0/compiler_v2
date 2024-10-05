#pragma once

class Visitor;

class Node {
public:
    virtual ~Node() = default;
    virtual void accept(Visitor &visitor) const = 0;
};

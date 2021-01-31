# 红黑树

## 步骤

- 创建基本node节点（即普通二叉树数据结构），包括颜色，左右子树
- 创建红黑树数据结构，包括红黑树基本操作
    - 左旋
    - 右旋
    - 变色
    - 注意两种变色情况
        - 插入节点后，其父节点两个子节点都是红色
        - 插入节点后，自身和父节点都是红色

## 数据结构

- node
    - 成员
        - lchild
        - rchild
        - color
        - key
        - value
    - 操作
        - rotateLeft(Node* node) -> node*
        - rotateRight(Node* node) -> node*
        - flipColors(Node* node)
- red black tree
    - 成员
        - root
    - 操作
        - 添加新的节点
        - 删除节点
    - 插入节点的总体情况：![image-2021012918163909](./images/image-20210129181639099.png)
    - 删除节点
        - 简单的删除最大值节点： 那个最大值正好存在红色父节点的左孩子
        - 简单的删除最小值节点： 最小值节点恰好为红色
        - 难点（自己制造红色节点）
            - 删除最大值节点: ![image-rotateRight](./images/deletemax1.png)
              ![image-rotateRight](./images/deletemax2.png)
            - 删除最小之节点: ![image-rotateLeft](./images/deletemin1.png)
              ![image-rotateLeft](./images/deletemin2.png)
            - 删除节点的原则： 当前节点或者孩子节点至少有一个为红色
            - 如果不满足上述原则
                - ![img_delete](./images/delete1.png)
                - ![img_delete](./images/delete2.png)

# 红黑树牛逼!!!

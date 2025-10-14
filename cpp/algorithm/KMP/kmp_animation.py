import matplotlib.pyplot as plt
import matplotlib.animation as animation

def kmp_steps(text, pattern):
    # 构造 next 数组
    def build_next(p):
        m = len(p)
        nxt = [0] * m
        j = 0
        for i in range(1, m):
            while j > 0 and p[i] != p[j]:
                j = nxt[j - 1]
            if p[i] == p[j]:
                j += 1
            nxt[i] = j
        return nxt

    next_array = build_next(pattern)
    n, m = len(text), len(pattern)
    j = 0
    steps = []

    for i in range(n):
        while j > 0 and text[i] != pattern[j]:
            steps.append((i, j, next_array[j-1], "mismatch"))
            j = next_array[j - 1]
        if text[i] == pattern[j]:
            steps.append((i, j, j+1, "match"))
            j += 1
        else:
            steps.append((i, j, j, "skip"))
        if j == m:
            steps.append((i, j, next_array[j-1], "found"))
            j = next_array[j - 1]
    return steps, next_array


def create_kmp_animation(text, pattern, filename="kmp.gif"):
    steps, next_array = kmp_steps(text, pattern)
    fig, ax = plt.subplots(figsize=(12, 3))

    def update(step_id):
        ax.clear()
        i, j, new_j, status = steps[step_id]

        # 绘制文本串
        ax.text(-1, 1, "Text:", fontsize=10, ha="right", va="center")
        for idx, ch in enumerate(text):
            ax.text(idx, 1, ch, fontsize=12, ha="center", va="center",
                    bbox=dict(boxstyle="round", fc="lightblue"))

        # 绘制模式串
        ax.text(-1, 0, "Pattern:", fontsize=10, ha="right", va="center")
        for k, ch in enumerate(pattern):
            ax.text(k + i - j, 0, ch, fontsize=12, ha="center", va="center",
                    bbox=dict(boxstyle="round", fc="lightgreen"))

        # 指针
        ax.annotate("i", xy=(i, 1.3), ha="center", fontsize=12, color="red")
        ax.annotate("j", xy=(i, -0.4), ha="center", fontsize=12, color="blue")

        # 提示信息
        if status == "mismatch":
            ax.text(len(text)+1, 0.5, f"失配: j 回退到 {new_j}", color="blue", fontsize=11)
        elif status == "match":
            ax.text(len(text)+1, 0.5, "匹配成功，i++, j++", color="green", fontsize=11)
        elif status == "skip":
            ax.text(len(text)+1, 0.5, "跳过: i++", color="gray", fontsize=11)
        elif status == "found":
            ax.text(len(text)+1, 0.5, "找到完整匹配!", color="purple", fontsize=11)

        ax.set_xlim(-2, len(text) + 6)
        ax.set_ylim(-1, 2)
        ax.axis("off")

    ani = animation.FuncAnimation(fig, update, frames=len(steps), interval=1000)
    ani.save(filename, writer="pillow")
    plt.close(fig)


if __name__ == "__main__":
    text = "ababcabcacbab"
    pattern = "abcac"
    create_kmp_animation(text, pattern, "kmp.gif")
    print("动画已生成：kmp.gif")


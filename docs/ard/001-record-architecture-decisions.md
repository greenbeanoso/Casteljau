# 0001. 紀錄架構決策 (Record Architecture Decisions)

## 狀態 (Status)
已接受 (Accepted)
*日期：2026-10-18*

## 背景 (Context)
- 隨著專案形象逐漸成形，我意識到需要一個穩定的方式來紀錄紀錄曾經技術上的取捨，才能兼顧開發效率與技術優化。

## 決策 (Decision)
我們決定採用 **ADR (Architecture Decision Record)** 架構決策紀錄機制：
1. **與程式碼共存：** 所有 ADR 將以 Markdown 檔案形式，存放在專案的 `docs/adr/` 目錄下。
2. **時序命名：** 檔案命名嚴格遵循 `[三位數序號]-[簡短主題].md` 的邏輯（例如 `002-encapsulate-window-manager.md`）。
3. **不可變性：** 決策一經合併即不可修改。若未來有新決策推翻舊決定，必須建立一篇全新的 ADR，並將舊 ADR 的狀態標記為 `Deprecated (已被取代)`，以保留完整的技術歷史。
4. **標準模板：** 每篇 ADR 必須包含「狀態 (Status)」、「背景 (Context)」、「決策 (Decision)」與「後果 (Consequences)」四個核心區塊。
```
# 標題

## 狀態 (Status)
[Proposed] 提案中 / [Accepted] 已接受 / [Deprecated] 已廢棄
*日期：0000-00-00*

## 背景 (Context)

## 決策 (Decision)

## 後果 (Consequences)
### 好處 (Pros) //可選(Optional)
### 缺點與風險 (Cons) //可選(Optional)
```
## 後果 (Consequences)
### 好處 (Pros)
- **歷史脈絡清晰：** 每一項重大技術變更都有據可查，方便日後溯源。
- **降低維護成本：** Markdown 格式極簡，撰寫成本低。

### 缺點與風險 (Cons)
- **額外文書成本：** 做出重大變更時需要花額外 5-10 分鐘撰寫檔案，初期需要建立主動記錄的習慣。

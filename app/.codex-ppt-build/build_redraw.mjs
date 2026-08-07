import fs from "node:fs/promises";
import { Presentation, PresentationFile } from "@oai/artifact-tool";

const OUT_DIR = "C:/Users/jiahui/Desktop/git/.codex-ppt-build/output";
const FINAL_PPTX = "C:/Users/jiahui/Desktop/git/new.ppt.pptx";
const FONT = "Microsoft YaHei";

async function writeBlob(path, blob) {
  await fs.writeFile(path, new Uint8Array(await blob.arrayBuffer()));
}

function lcg(seed) {
  let state = seed >>> 0;
  return function random() {
    state = (1664525 * state + 1013904223) >>> 0;
    return state / 4294967296;
  };
}

const presentation = Presentation.create({ slideSize: { width: 1800, height: 1200 } });
const slide = presentation.slides.add();
slide.background.fill = "#F4F8FB";
const curveArrowHeads = [];

function addShape(name, geometry, position, fill, line, radius, shadow) {
  const config = {
    geometry,
    name,
    position,
    fill,
    line: line || { style: "solid", fill: "none", width: 0 },
  };
  if (radius !== undefined) config.borderRadius = radius;
  if (shadow) config.shadow = shadow;
  return slide.shapes.add(config);
}

function addText(name, text, position, size, color, bold, align, valign, fill, line, radius) {
  const shape = addShape(
    name,
    radius ? "roundRect" : "textbox",
    position,
    fill || "none",
    line || { style: "solid", fill: "none", width: 0 },
    radius,
  );
  shape.text = text;
  shape.text.style = {
    fontSize: size,
    typeface: FONT,
    color,
    bold: Boolean(bold),
    alignment: align || "left",
    verticalAlignment: valign || "middle",
    autoFit: "shrinkText",
    wrap: "none",
    insets: { left: 2, right: 2, top: 1, bottom: 1 },
  };
  return shape;
}

function addLine(name, x1, y1, x2, y2, color, width, style) {
  const left = Math.min(x1, x2);
  const top = Math.min(y1, y2);
  const dx = Math.abs(x2 - x1);
  const dy = Math.abs(y2 - y1);
  const negativeSlope = (x2 - x1) * (y2 - y1) < 0;
  return addShape(
    name,
    "line",
    {
      left,
      top,
      width: Math.max(dx, 0.5),
      height: Math.max(dy, 0.5),
      verticalFlip: negativeSlope,
    },
    "none",
    { style: style || "solid", fill: color, width },
  );
}

function addPolyline(name, points, color, width, style) {
  const xs = points.map((p) => p.x);
  const ys = points.map((p) => p.y);
  const left = Math.min(...xs);
  const top = Math.min(...ys);
  const pathWidth = Math.max(Math.max(...xs) - left, 1);
  const pathHeight = Math.max(Math.max(...ys) - top, 1);
  const commands = [{ moveTo: { x: points[0].x - left, y: points[0].y - top } }];
  for (let i = 1; i < points.length; i += 1) {
    commands.push({ lineTo: { x: points[i].x - left, y: points[i].y - top } });
  }
  return slide.shapes.add({
    geometry: "custom",
    name,
    position: { left, top, width: pathWidth, height: pathHeight },
    fill: "none",
    line: { style: style || "solid", fill: color, width },
    customPaths: [{ width: pathWidth, height: pathHeight, commands }],
  });
}

function quadraticPoints(p0, p1, p2, count) {
  const points = [];
  for (let i = 0; i <= count; i += 1) {
    const t = i / count;
    const u = 1 - t;
    points.push({
      x: u * u * p0.x + 2 * u * t * p1.x + t * t * p2.x,
      y: u * u * p0.y + 2 * u * t * p1.y + t * t * p2.y,
    });
  }
  return points;
}

function addArrowHead(name, from, to, color, size) {
  const angle = Math.atan2(to.y - from.y, to.x - from.x) * 180 / Math.PI;
  return addShape(
    name,
    "triangle",
    { left: to.x - size / 2, top: to.y - size / 2, width: size, height: size, rotation: angle + 90 },
    color,
    { style: "solid", fill: color, width: 0.5 },
  );
}

function addCurveArrow(name, p0, p1, p2, color, width, size) {
  const pts = quadraticPoints(p0, p1, p2, 28);
  addPolyline(name + "-path", pts, color, width);
  const head = addArrowHead(name + "-head", pts[pts.length - 2], pts[pts.length - 1], color, size);
  curveArrowHeads.push(head);
}

function addPill(name, text, x, y, w, h, fill, stroke, textColor, size) {
  return addText(
    name,
    text,
    { left: x, top: y, width: w, height: h },
    size || 18,
    textColor,
    true,
    "center",
    "middle",
    fill,
    { style: "solid", fill: stroke, width: 1 },
    h / 2,
  );
}

function addRockSample(name, x, y, w, h, seed) {
  const rnd = lcg(seed);
  addShape(name + "-base", "roundRect", { left: x, top: y, width: w, height: h }, "#7D8991", { style: "solid", fill: "#18344B", width: 2 }, 18);
  const stoneColors = ["#B7BEC2", "#C7CDD0", "#A7B0B5", "#D1D5D7", "#929DA4", "#BBC2C6"];
  const rows = 4;
  const cols = 9;
  const cellW = (w - 20) / cols;
  const cellH = (h - 16) / rows;
  let index = 0;
  for (let row = 0; row < rows; row += 1) {
    for (let col = 0; col < cols; col += 1) {
      const sw = cellW * (0.72 + rnd() * 0.55);
      const sh = cellH * (0.62 + rnd() * 0.65);
      const sx = x + 10 + col * cellW + (cellW - sw) / 2 + (rnd() - 0.5) * 8;
      const sy = y + 8 + row * cellH + (cellH - sh) / 2 + (rnd() - 0.5) * 6;
      addShape(
        name + "-stone-" + index,
        "ellipse",
        { left: sx, top: sy, width: sw, height: sh, rotation: -25 + rnd() * 50 },
        stoneColors[Math.floor(rnd() * stoneColors.length)],
        { style: "solid", fill: "#DCE1E4", width: 0.45 },
      );
      index += 1;
    }
  }
  for (let i = 0; i < 18; i += 1) {
    const px = x + 12 + rnd() * (w - 24);
    const py = y + 9 + rnd() * (h - 18);
    const len = 10 + rnd() * 23;
    const ang = rnd() * Math.PI * 2;
    const mx = px + Math.cos(ang) * len * 0.55;
    const my = py + Math.sin(ang) * len * 0.55;
    const ex = px + Math.cos(ang + (rnd() - 0.5) * 0.8) * len;
    const ey = py + Math.sin(ang + (rnd() - 0.5) * 0.8) * len;
    addPolyline(name + "-microcrack-" + i, [{ x: px, y: py }, { x: mx, y: my }, { x: ex, y: ey }], "#E8EEF1", 0.8);
  }
  addShape(name + "-border", "roundRect", { left: x, top: y, width: w, height: h }, "none", { style: "solid", fill: "#18344B", width: 2.2 }, 18);
}

// Background grid and outer frame.
for (let x = 0; x <= 1800; x += 40) addLine("grid-v-" + x, x, 0, x, 1200, "#E8F0F5", 0.8);
for (let y = 0; y <= 1200; y += 40) addLine("grid-h-" + y, 0, y, 1800, y, "#E8F0F5", 0.8);
addShape("outer-frame", "roundRect", { left: 16, top: 17, width: 1768, height: 1166 }, "none", { style: "solid", fill: "#D5E2EB", width: 2 }, 28);

// Main white surfaces.
addShape("top-card", "roundRect", { left: 62, top: 47, width: 1676, height: 303 }, "#FFFFFF", { style: "solid", fill: "#D9E4EB", width: 1 }, 34, "shadow-sm");
addShape("bottom-card", "roundRect", { left: 62, top: 386, width: 1676, height: 759 }, "#FFFFFF", { style: "solid", fill: "#D9E4EB", width: 1 }, 34, "shadow-sm");

// Upper process title.
addText("process-title", "加载—变形—抽采过程", { left: 96, top: 65, width: 420, height: 34 }, 25, "#102F45", true);
addText("process-subtitle", "循环扰动驱动裂隙演化与瓦斯运移", { left: 96, top: 101, width: 460, height: 25 }, 17, "#8298AA", false);

// Stage panels.
const stagePanels = [95, 660, 1225];
for (let i = 0; i < 3; i += 1) {
  addShape("stage-panel-" + (i + 1), "roundRect", { left: stagePanels[i], top: 143, width: 480, height: 175 }, "#F9FBFD", { style: "solid", fill: "#D6E3EC", width: 1 }, 23);
  const badge = addShape("stage-badge-" + (i + 1), "ellipse", { left: stagePanels[i] + 17, top: 158, width: 41, height: 41 }, "#173D58", { style: "solid", fill: "#173D58", width: 1 });
  badge.text = String(i + 1);
  badge.text.style = { fontSize: 17, typeface: FONT, color: "#FFFFFF", bold: true, alignment: "center", verticalAlignment: "middle", insets: { left: 0, right: 0, top: 0, bottom: 0 } };
}
addShape("process-arrow-1", "triangle", { left: 594, top: 213, width: 29, height: 34, rotation: 90 }, "#88A1B5", { style: "solid", fill: "#88A1B5", width: 0.5 });
addShape("process-arrow-2", "triangle", { left: 1159, top: 213, width: 29, height: 34, rotation: 90 }, "#88A1B5", { style: "solid", fill: "#88A1B5", width: 0.5 });

// Stage 1: cyclic loading/unloading.
addRockSample("sample-1", 130, 196, 245, 84, 11);
addShape("load-bar-top", "roundRect", { left: 178, top: 178, width: 150, height: 13 }, "#D94051", { style: "solid", fill: "#D94051", width: 0 }, 7);
addShape("load-bar-bottom", "roundRect", { left: 178, top: 285, width: 150, height: 13 }, "#D94051", { style: "solid", fill: "#D94051", width: 0 }, 7);
for (const tx of [205, 250, 295]) {
  addLine("top-load-tick-" + tx, tx, 175, tx, 197, "#D94051", 3);
  addLine("bottom-load-tick-" + tx, tx, 282, tx, 302, "#D94051", 3);
}
addText("stage-1-label", "循环加卸载", { left: 392, top: 214, width: 160, height: 50 }, 30, "#112B40", true, "left");

// Stage 2: plastic deformation and macro-fractures.
addRockSample("sample-2", 695, 196, 245, 84, 22);
const yellow = "#FFD53E";
[
  [{ x: 735, y: 216 }, { x: 748, y: 237 }, { x: 763, y: 259 }, { x: 742, y: 274 }],
  [{ x: 816, y: 219 }, { x: 824, y: 244 }, { x: 838, y: 266 }, { x: 817, y: 278 }],
  [{ x: 897, y: 215 }, { x: 905, y: 244 }, { x: 918, y: 261 }, { x: 934, y: 255 }, { x: 950, y: 286 }],
  [{ x: 756, y: 262 }, { x: 776, y: 255 }, { x: 799, y: 286 }],
  [{ x: 835, y: 269 }, { x: 851, y: 258 }, { x: 870, y: 301 }],
].forEach((pts, i) => addPolyline("fracture-yellow-" + i, pts, yellow, 3.5));
addText("stage-2-label", "塑性变形", { left: 974, top: 214, width: 165, height: 50 }, 30, "#112B40", true, "left");

// Stage 3: extraction point and radial gas flow.
addRockSample("sample-3", 1260, 196, 245, 84, 33);
const cx = 1382;
const cy = 238;
const cyan = "#45C4E4";
for (let i = 0; i < 12; i += 1) {
  const a = (i / 12) * Math.PI * 2;
  const r1 = 31;
  const r2 = i % 2 === 0 ? 69 : 58;
  const p1 = { x: cx + Math.cos(a) * r1, y: cy + Math.sin(a) * r1 };
  const p2 = { x: cx + Math.cos(a) * r2, y: cy + Math.sin(a) * r2 };
  addLine("gas-ray-" + i, p1.x, p1.y, p2.x, p2.y, cyan, 2.2);
  addArrowHead("gas-ray-head-" + i, p1, p2, cyan, 9);
}
addShape("extraction-outer", "ellipse", { left: cx - 21, top: cy - 21, width: 42, height: 42 }, "#FFFFFF", { style: "solid", fill: "#EF3F46", width: 5 });
addShape("extraction-inner", "ellipse", { left: cx - 10, top: cy - 10, width: 20, height: 20 }, cyan, { style: "solid", fill: cyan, width: 1 });
addLine("extraction-line", 1506, cy, 1538, cy, cyan, 6);
addText("stage-3-label", "瓦斯抽采", { left: 1538, top: 214, width: 135, height: 50 }, 30, "#112B40", true, "left");

// Lower panel title.
addText("coupling-title", "多场耦合关系", { left: 96, top: 409, width: 300, height: 34 }, 25, "#102F45", true);
addText("coupling-subtitle", "损伤场驱动材料参数演化，三类物理场双向反馈", { left: 96, top: 446, width: 520, height: 25 }, 17, "#8298AA", false);

// Coupling connectors are created before entity nodes so they sit behind boxes and labels.
addCurveArrow("diffusion-to-stress-blue-light", { x: 750, y: 500 }, { x: 420, y: 570 }, { x: 340, y: 875 }, "#42A9D8", 6.5, 16);
addCurveArrow("diffusion-to-stress-blue-dark", { x: 750, y: 531 }, { x: 500, y: 590 }, { x: 405, y: 875 }, "#1D6A9A", 6.5, 16);
addCurveArrow("diffusion-to-seepage-green-light", { x: 1050, y: 500 }, { x: 1390, y: 560 }, { x: 1460, y: 875 }, "#48B983", 6.5, 16);
addCurveArrow("diffusion-to-seepage-green-dark", { x: 1050, y: 531 }, { x: 1310, y: 590 }, { x: 1392, y: 875 }, "#176441", 6.5, 16);
addCurveArrow("damage-to-diffusion", { x: 900, y: 706 }, { x: 900, y: 645 }, { x: 900, y: 576 }, "#F29B65", 7, 17);
addCurveArrow("damage-to-stress", { x: 786, y: 852 }, { x: 620, y: 882 }, { x: 478, y: 894 }, "#7185BD", 7, 17);
addCurveArrow("damage-to-seepage", { x: 1014, y: 852 }, { x: 1165, y: 879 }, { x: 1325, y: 895 }, "#D96678", 7, 17);
addCurveArrow("seepage-to-stress", { x: 1338, y: 990 }, { x: 900, y: 1125 }, { x: 465, y: 990 }, "#ED1F3E", 7, 18);
addCurveArrow("stress-to-seepage-bottom", { x: 464, y: 1028 }, { x: 900, y: 1210 }, { x: 1335, y: 1028 }, "#F1879C", 7, 18);

// Entity nodes.
const diffusion = addShape("diffusion-node", "roundRect", { left: 750, top: 465, width: 300, height: 111 }, "#E7F6F0", { style: "solid", fill: "#169965", width: 2 }, 24, "shadow-sm");
addShape("diffusion-icon-ring", "ellipse", { left: 779, top: 489, width: 60, height: 60 }, "#F2FBF7", { style: "solid", fill: "#169965", width: 1.6 });
[
  [801, 503, 16], [784, 518, 14], [816, 520, 13], [802, 532, 11],
].forEach((d, i) => addShape("diffusion-dot-" + i, "ellipse", { left: d[0], top: d[1], width: d[2], height: d[2] }, "#25A173", { style: "solid", fill: "#25A173", width: 0 }));
addText("diffusion-label", "扩散场", { left: 885, top: 490, width: 132, height: 58 }, 34, "#0C3045", true, "center");

const stress = addShape("stress-node", "roundRect", { left: 188, top: 875, width: 300, height: 110 }, "#FDEEF1", { style: "solid", fill: "#D7415A", width: 2 }, 24, "shadow-sm");
addShape("stress-icon-box", "roundRect", { left: 224, top: 910, width: 43, height: 39 }, "#FFFFFF", { style: "solid", fill: "#D7415A", width: 1.8 }, 4);
addLine("stress-icon-left-line", 198, 930, 219, 930, "#D7415A", 3);
addArrowHead("stress-icon-left-arrow", { x: 198, y: 930 }, { x: 219, y: 930 }, "#D7415A", 9);
addLine("stress-icon-right-line", 293, 930, 272, 930, "#D7415A", 3);
addArrowHead("stress-icon-right-arrow", { x: 293, y: 930 }, { x: 272, y: 930 }, "#D7415A", 9);
addText("stress-label", "应力场", { left: 324, top: 899, width: 136, height: 58 }, 34, "#0C3045", true, "center");

const seepage = addShape("seepage-node", "roundRect", { left: 1312, top: 875, width: 300, height: 110 }, "#FFF1E1", { style: "solid", fill: "#D77A20", width: 2 }, 24, "shadow-sm");
for (let i = 0; i < 3; i += 1) {
  const yy = 914 + i * 16;
  addLine("seepage-icon-line-" + i, 1341, yy, 1400, yy, "#D77A20", 3);
  addArrowHead("seepage-icon-head-" + i, { x: 1378, y: yy }, { x: 1400, y: yy }, "#D77A20", 9);
}
addText("seepage-label", "渗流场", { left: 1450, top: 899, width: 136, height: 58 }, 34, "#0C3045", true, "center");

const damageOuter = addShape("damage-node-outer", "ellipse", { left: 785, top: 705, width: 230, height: 230 }, "#EDF7FC", { style: "solid", fill: "#1E6C9E", width: 2.8 }, undefined, "shadow-sm");
addShape("damage-node-inner", "ellipse", { left: 807, top: 727, width: 186, height: 186 }, "#70B3DF", { style: "solid", fill: "#70B3DF", width: 1 });
addPolyline("damage-crack-main", [{ x: 900, y: 742 }, { x: 883, y: 770 }, { x: 906, y: 788 }, { x: 884, y: 808 }, { x: 913, y: 827 }], "#123F5D", 4);
addLine("damage-crack-left-top", 883, 770, 859, 782, "#123F5D", 4);
addLine("damage-crack-right", 906, 788, 936, 771, "#123F5D", 4);
addLine("damage-crack-left-bottom", 884, 808, 859, 793, "#123F5D", 4);
addText("damage-label", "损伤场", { left: 837, top: 838, width: 126, height: 53 }, 34, "#0C3045", true, "center");

// Keep connector paths behind nodes, but expose their arrowheads above node borders.
for (const head of curveArrowHeads) head.bringToFront();

// Relationship labels.
addPill("label-effective-stress", "有效应力，吸附膨胀", 380, 563, 270, 42, "#F2F9FD", "#A9D4EB", "#175B82", 18);
addPill("label-porosity-permeability", "基于孔隙率和渗透率", 229, 679, 292, 43, "#F0FAFE", "#A9DCEC", "#1B6D91", 18);
addPill("label-mass-positive", "质量交换（正）", 1175, 563, 220, 42, "#F1FAF6", "#B8DFCD", "#246D52", 18);
addPill("label-mass-negative", "质量交换（负）", 1313, 679, 220, 43, "#F1FAF6", "#B8DFCD", "#247D59", 18);
addPill("label-porosity", "孔隙率", 938, 627, 126, 42, "#FFF8F4", "#F3B88F", "#B15D38", 18);
addPill("label-damage", "损伤", 589, 798, 104, 42, "#F7F8FD", "#C8D0E6", "#526A9A", 18);
addPill("label-young-cohesion", "杨氏模量 / 内聚力", 482, 856, 249, 43, "#F7F8FD", "#CFD5E7", "#536A96", 17);
addPill("label-permeability", "渗透率", 1106, 798, 126, 42, "#FFF6F7", "#F3BCC5", "#AE4557", 18);
addPill("label-pore-pressure", "孔隙压力", 823, 982, 155, 42, "#FFF7F8", "#F4B9C1", "#C83249", 18);
addPill("label-crack-properties", "裂隙孔隙率和渗透率", 748, 1089, 305, 43, "#FFF7F8", "#F2BCC6", "#C44759", 17);

// Provenance note. The image is only a visual reference and is not embedded in the deck.
slide.speakerNotes.textFrame.setText("[Sources]\n- User-provided reference image: C:/Users/jiahui/AppData/Local/Temp/codex-clipboard-18084e59-2b3a-41a9-a288-74d6b9f4ed5e.png (used only for visual reconstruction; not embedded)");

await fs.mkdir(OUT_DIR, { recursive: true });
const preview = await presentation.export({ slide, format: "png", scale: 1 });
await writeBlob(OUT_DIR + "/slide-1.png", preview);
const layout = await slide.export({ format: "layout" });
await fs.writeFile(OUT_DIR + "/slide-1.layout.json", await layout.text());
const montage = await presentation.export({ format: "webp", montage: true, scale: 1 });
await writeBlob(OUT_DIR + "/montage.webp", montage);
const pptx = await PresentationFile.exportPptx(presentation);
await pptx.save(FINAL_PPTX);

const inspect = await presentation.inspect({ kind: "slide,textbox,shape,notes", maxChars: 12000 });
await fs.writeFile(OUT_DIR + "/inspect.ndjson", inspect.ndjson);
console.log(FINAL_PPTX);

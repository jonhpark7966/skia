/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkSGText_DEFINED
#define SkSGText_DEFINED

#include "SkSGGeometryNode.h"

#include "SkPaintDefaults.h"
#include "SkPoint.h"
#include "SkString.h"
#include "SkTextBlob.h"
#include "SkTextUtils.h"

class SkCanvas;
class SkPaint;
class SkTypeface;

namespace sksg {

/**
 * Concrete Geometry node, wrapping a (shaped) SkTextBlob.
 */
class Text final : public GeometryNode {
public:
    static sk_sp<Text> Make(sk_sp<SkTypeface> tf, const SkString& text);
    ~Text() override;

    SG_ATTRIBUTE(Typeface, sk_sp<SkTypeface>, fTypeface)
    SG_ATTRIBUTE(Text    , SkString         , fText    )
    SG_ATTRIBUTE(Flags   , uint32_t         , fFlags   )
    SG_ATTRIBUTE(Position, SkPoint          , fPosition)
    SG_ATTRIBUTE(Size    , SkScalar         , fSize    )
    SG_ATTRIBUTE(ScaleX  , SkScalar         , fScaleX  )
    SG_ATTRIBUTE(SkewX   , SkScalar         , fSkewX   )
    SG_ATTRIBUTE(Align   , SkTextUtils::Align   , fAlign   )
    SG_ATTRIBUTE(Hinting , SkPaint::Hinting , fHinting )

    // TODO: add shaping functionality.

protected:
    void onClip(SkCanvas*, bool antiAlias) const override;
    void onDraw(SkCanvas*, const SkPaint&) const override;

    SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;
    SkPath onAsPath() const override;

private:
    Text(sk_sp<SkTypeface>, const SkString&);

    SkPoint alignedPosition(SkScalar advance) const;

    sk_sp<SkTypeface> fTypeface;
    SkString                fText;
    uint32_t                fFlags    = SkPaintDefaults_Flags;
    SkPoint                 fPosition = SkPoint::Make(0, 0);
    SkScalar                fSize     = SkPaintDefaults_TextSize;
    SkScalar                fScaleX   = 1;
    SkScalar                fSkewX    = 0;
    SkTextUtils::Align      fAlign    = SkTextUtils::kLeft_Align;
    SkPaint::Hinting        fHinting  = SkPaintDefaults_Hinting;

    sk_sp<SkTextBlob> fBlob; // cached text blob

    using INHERITED = GeometryNode;
};

/**
 * Concrete Geometry node, wrapping an external SkTextBlob.
 */
class TextBlob final : public GeometryNode {
public:
    static sk_sp<TextBlob> Make(sk_sp<SkTextBlob> = nullptr);
    ~TextBlob() override;

    SG_ATTRIBUTE(Blob    , sk_sp<SkTextBlob>, fBlob    )
    SG_ATTRIBUTE(Position, SkPoint          , fPosition)

protected:
    void onClip(SkCanvas*, bool antiAlias) const override;
    void onDraw(SkCanvas*, const SkPaint&) const override;

    SkRect onRevalidate(InvalidationController*, const SkMatrix&) override;
    SkPath onAsPath() const override;

private:
    explicit TextBlob(sk_sp<SkTextBlob>);

    sk_sp<SkTextBlob> fBlob;
    SkPoint           fPosition = SkPoint::Make(0, 0);

    using INHERITED = GeometryNode;
};
} // namespace sksg

#endif // SkSGText_DEFINED

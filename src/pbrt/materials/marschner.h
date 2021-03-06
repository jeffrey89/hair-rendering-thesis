
/*
 Dual hair scattering algorithm for PBRT
 */

#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef MARSCHNERMATERIAL_H
#define MARSCHNERMATERIAL_H

// materials/marschner.h*
#include "pbrt.h"
#include "material.h"
#include "reflection.h"

namespace pbrt {
    
    class MarschnerBSDF;
    
    struct MarschnerAngles {
        MarschnerAngles(const Vector3f& wo, const Vector3f& wi, Float eta = 1.55, Float eccentricity = 1.0);
        
        Float thetaI, thetaR, phiI, phiR;
        Float thetaD, thetaH;
        Float phi, phiH;
        Float etaPerp, etaPar;
        Float sinThetaR, sinThetaT, cosThetaT;
        
    };
    
    // PlasticMaterial Declarations
    class MarschnerMaterial : public Material {
      public:
        MarschnerMaterial(const Float alpha[], 
                        const Float beta[], 
                        Float hairRadius,
                        Float eta, 
                        Float eccentricity, 
                        Float glintScaleFactor, 
                        Float causticWidth, 
                        Float causticFade, 
                        Float causticLimit,
                        const std::shared_ptr<Texture<Spectrum>> &sigmaA) 
            : mAr(alpha[0]), mAtt(alpha[1]), mAtrt(alpha[2]),                
            mBr(beta[0]), mBtt(beta[1]), mBtrt(beta[2]),
            mHairRadius(hairRadius), 
            mEta(eta), 
            mEccentricity(eccentricity), 
            mGlintScaleFactor(glintScaleFactor), 
            mCausticWidth(causticWidth), 
            mCausticFadeRange(causticFade), 
            mCausticIntensityLimit(causticLimit),
            mSigmaA(sigmaA)
            {}

        MarschnerBSDF* CreateMarschnerBSDF(SurfaceInteraction *si, MemoryArena &arena) const;
        void ComputeScatteringFunctions(SurfaceInteraction *si, MemoryArena &arena,
                                        TransportMode mode,
                                        bool allowMultipleLobes) const;

      public:
        Float mAr, mAtt, mAtrt;
        Float mBr, mBtt, mBtrt;
        Float mHairRadius, mEta, mEccentricity, mGlintScaleFactor, 
        mCausticWidth, mCausticFadeRange, mCausticIntensityLimit;
        std::shared_ptr<Texture<Spectrum>> mSigmaA, mKd;
    };
    
    // MarschnerBSDF Declarations
    class MarschnerBSDF : public BxDF {        
      public:
        MarschnerBSDF(const SurfaceInteraction& si, 
                Float alphaR, Float alphaTT, Float alphaTRT, 
                Float betaR, Float betaTT, Float betaTRT, 
                Float hairRadius, Float eta, Spectrum sigmaA,
                Float eccentricity, Float glintScaleFactor, Float causticWidth, Float causticFadeRange, Float causticIntensityLimit);
        
        /**
         * (Required) Returns the value of the distribution function for the given pair of directions
         *
         * @param wo outgoing direction
         * @param wi incoming direction
         * @return
         */
        virtual Spectrum f(const Vector3f &wo, const Vector3f &wi) const;
        Float f_Weighted(const Vector3f &wo, const Vector3f &wi, Float w0, Float w1, Float w2) const;
        
        
        Spectrum f_p(int p, const Vector3f &wo, const Vector3f &wi) const;
        Spectrum f_r(const Vector3f &wo, const Vector3f &wi) const;
        Spectrum f_tt(const Vector3f &wo, const Vector3f &wi) const;
        Spectrum f_trt(const Vector3f &wo, const Vector3f &wi) const;
        
        /**
         * Returns the value of the distribution function for the given pair of directions.
         *
         * Used for handling scattering that is described by delta distributions
         * as well as for randomly sampling directions from BxDFs that scatter
         * light along multiple directions.
         *
         * @param wo outgoing direction
         * @param wi incoming direction
         * @param sample
         * @param pdf
         * @param sampledType
         * @return
         */
        virtual Spectrum Sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &sample, Float *pdf, BxDFType *sampledType = nullptr) const;
        
        /**
         * Returns the probability density function between the incoming and outgoing direction.
         * In other words, how likely is it that incoming radiance is reflected
         * (or refracted) towards the outgoing direction.
         * @param wo
         * @param wi
         * @return 
         */       
        virtual Float Pdf(const Vector3f &wo, const Vector3f &wi) const;
        
        /**
         * 
         * @return 
         */
        virtual std::string ToString() const;
        
        Float M_r(Float theta_h) const;
        Float M_tt(Float theta_h) const;
        Float M_trt(Float theta_h) const;

        Float M_r(Float thetaI, Float thetaR) const;
        Float M_tt(Float thetaI, Float thetaR) const;
        Float M_trt(Float thetaI, Float thetaR) const;

        
        Spectrum N_r(Float relativePhi, Float etaPerp) const;
        Spectrum N_tt(Float relativePhi, Float etaPerp, Float cosThetaT) const;
        Spectrum N_trt(Float relativePhi, Float etaPerp, Float cosThetaT) const;
        
        Float N_r_absorption(Float dphi, Float absorption) const;
        Float N_tt_absorption(Float dphi, Float etaPerp, Float absorption) const;
        Float N_trt_absorption(Float dphi, Float etaPerp, Float absorption) const;
        
        //TODO: is this needed to expose?
        
        // Not implemented for now
        //virtual Spectrum rho(const Vector3f &wo, int nSamples, const Point2f *samples) const;
        //virtual Spectrum rho(int nSamples, const Point2f *samples1, const Point2f *samples2) const;
        
        Float getEccentricity() const;

        const Spectrum& getSigmaA() const;
    private:
        const Normal3f mNs, mNg;
        const Vector3f mDpdu, mDpdv;

        // Marschner params
        const Float mAlphaR, mAlphaTT, mAlphaTRT, mBetaR, mBetaTT, mBetaTRT;
        const Float mHairRadius = 1.0;
        const Float mEta, mEccentricity, mGlintScaleFactor, 
        mCausticWidth, mCausticFadeRange, mCausticIntensityLimit;
        Spectrum mSigmaA;
        

       
        
        
        
        void applySurfaceRoughness(Spectrum& L, const Spectrum& absorption, Float relativePhi, Float etaPerp) const;
    };

    MarschnerMaterial *CreateMarschnerMaterial(const TextureParams &mp);

}  // namespace pbrt

#endif  // MARSCHNERMATERIAL_H
